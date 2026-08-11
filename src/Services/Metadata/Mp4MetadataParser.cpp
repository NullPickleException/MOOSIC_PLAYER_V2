//==============================================================================
// Mp4MetadataParser.cpp
//==============================================================================
// Custom binary parser for MP4/M4A metadata (iTunes atoms, cover art)
// OPTIMIZED: Targeted reads - only reads metadata atoms, not the entire file
//==============================================================================

#include "Mp4MetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool Mp4MetadataParser::Parse(const std::filesystem::path& filePath,
                               MusicTrack& track,
                               bool extractAlbumArt) const
{
    size_t fileSize = GetFileSize(filePath);
    if (fileSize < 8) return false;

    // Read only the first 8 bytes to check for ftyp/moov
    auto header = ReadFileHead(filePath, 8);
    if (header.size() < 8) return false;

    return ParseAtoms(filePath, track, extractAlbumArt);
}

//==============================================================================
// Optimized File Reading Helpers
//==============================================================================

size_t Mp4MetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> Mp4MetadataParser::ReadFileRange(const std::filesystem::path& filePath,
                                                       size_t offset, size_t length) const
{
    if (length == 0 || length > 100 * 1024 * 1024) return {};
    
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return {};
    
    file.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
    if (!file.good()) return {};
    
    std::vector<uint8_t> buffer(length);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(length)))
    {
        size_t actualRead = static_cast<size_t>(file.gcount());
        if (actualRead == 0) return {};
        buffer.resize(actualRead);
    }
    
    return buffer;
}

std::vector<uint8_t> Mp4MetadataParser::ReadFileHead(const std::filesystem::path& filePath,
                                                       size_t length) const
{
    return ReadFileRange(filePath, 0, length);
}

//==============================================================================
// Atom Tree Parser (uses targeted reads)
//==============================================================================

bool Mp4MetadataParser::ParseAtoms(const std::filesystem::path& filePath,
                                    MusicTrack& track,
                                    bool extractAlbumArt) const
{
    size_t fileSize = GetFileSize(filePath);
    bool hasMetadata = false;

    // Stack for atom traversal: offset, size pairs
    std::vector<std::pair<size_t, size_t>> atomStack;
    atomStack.push_back({0, fileSize});

    while (!atomStack.empty())
    {
        auto [parentOffset, parentEnd] = atomStack.back();
        atomStack.pop_back();

        size_t offset = parentOffset;

        // Read atom headers in chunks to minimize disk reads
        while (offset + 8 <= parentEnd)
        {
            // Read just the atom header (8 bytes)
            auto headerData = ReadFileRange(filePath, offset, 8);
            if (headerData.size() < 8) break;

            uint32_t atomSize = ReadUInt32BE(headerData, 0);
            std::string atomType = ReadString(headerData, 4, 4);

            if (atomSize < 8) break;
            if (offset + atomSize > parentEnd) break;

            if (atomType == "moov" || atomType == "udta")
            {
                // Push container atom to stack
                atomStack.push_back({offset + 8, offset + atomSize});
            }
            else if (atomType == "meta")
            {
                hasMetadata |= ParseMetaAtom(filePath, offset + 8, atomSize - 8, track, extractAlbumArt);
            }
            else if (atomType == "ilst")
            {
                hasMetadata |= ParseILST(filePath, offset + 8, atomSize - 8, track, extractAlbumArt);
            }

            offset += atomSize;
        }
    }

    return hasMetadata;
}

//==============================================================================
// Meta Atom (contains ilst)
//==============================================================================

bool Mp4MetadataParser::ParseMetaAtom(const std::filesystem::path& filePath,
                                       size_t atomOffset, size_t atomSize,
                                       MusicTrack& track,
                                       bool extractAlbumArt) const
{
    // Skip 4-byte version/flags
    return ParseILST(filePath, atomOffset + 4, atomSize - 4, track, extractAlbumArt);
}

//==============================================================================
// iTunes Metadata List Parser
//==============================================================================

bool Mp4MetadataParser::ParseILST(const std::filesystem::path& filePath,
                                   size_t offset, size_t length,
                                   MusicTrack& track,
                                   bool extractAlbumArt) const
{
    // Read the entire ilst atom (typically small, a few KB)
    size_t readSize = (std::min)(length, static_cast<size_t>(1 * 1024 * 1024)); // Cap at 1MB
    auto data = ReadFileRange(filePath, offset, readSize);
    if (data.empty()) return false;

    size_t end = data.size();
    size_t pos = 0;
    bool hasMetadata = false;

    while (pos + 8 <= end)
    {
        uint32_t atomSize = ReadUInt32BE(data, pos);
        std::string atomType = ReadString(data, pos + 4, 4);

        if (atomSize == 0 || atomSize > end - pos) break;

        //------------------------------------------------------------------
        // Title: ©nam or titl
        //------------------------------------------------------------------
        if (IsAppleMetaAtom(atomType, "nam") || atomType == "titl")
        {
            if (pos + 16 <= end)
            {
                uint16_t valueLength = ReadUInt16BE(data, pos + 14);
                if (pos + 16 + valueLength <= end)
                {
                    track.SetTitle(CleanString(ReadString(data, pos + 16, valueLength)));
                    hasMetadata = true;
                }
            }
        }
        //------------------------------------------------------------------
        // Artist: ©ART or "art "
        //------------------------------------------------------------------
        else if (IsAppleMetaAtom(atomType, "ART") || (atomType.size() == 4 && atomType[0] == 'a' && atomType[1] == 'r' && atomType[2] == 't' && atomType[3] == ' '))
        {
            if (pos + 16 <= end)
            {
                uint16_t valueLength = ReadUInt16BE(data, pos + 14);
                if (pos + 16 + valueLength <= end)
                {
                    track.SetArtist(CleanString(ReadString(data, pos + 16, valueLength)));
                    hasMetadata = true;
                }
            }
        }
        //------------------------------------------------------------------
        // Album: ©alb or albm
        //------------------------------------------------------------------
        else if (IsAppleMetaAtom(atomType, "alb") || atomType == "albm")
        {
            if (pos + 16 <= end)
            {
                uint16_t valueLength = ReadUInt16BE(data, pos + 14);
                if (pos + 16 + valueLength <= end)
                    track.SetAlbum(CleanString(ReadString(data, pos + 16, valueLength)));
            }
        }
        //------------------------------------------------------------------
        // Genre: ©gen or gnre
        //------------------------------------------------------------------
        else if (IsAppleMetaAtom(atomType, "gen") || atomType == "gnre")
        {
            if (pos + 16 <= end)
            {
                uint16_t valueLength = ReadUInt16BE(data, pos + 14);
                if (pos + 16 + valueLength <= end)
                    track.SetGenre(CleanString(ReadString(data, pos + 16, valueLength)));
            }
        }
        //------------------------------------------------------------------
        // Year: ©day or "day "
        //------------------------------------------------------------------
        else if (IsAppleMetaAtom(atomType, "day") || (atomType.size() == 4 && atomType[0] == 'd' && atomType[1] == 'a' && atomType[2] == 'y' && atomType[3] == ' '))
        {
            if (pos + 16 <= end)
            {
                uint16_t valueLength = ReadUInt16BE(data, pos + 14);
                if (pos + 16 + valueLength <= end)
                {
                    try { track.SetYear(std::stoi(ReadString(data, pos + 16, valueLength))); }
                    catch (...) {}
                }
            }
        }
        //------------------------------------------------------------------
        // Track number: trkn
        //------------------------------------------------------------------
        else if (atomType == "trkn")
        {
            if (pos + 24 <= end)
                track.SetTrackNumber(ReadUInt32BE(data, pos + 20));
        }
        //------------------------------------------------------------------
        // Cover art: covr (ONLY if extractAlbumArt is true)
        //------------------------------------------------------------------
        else if (atomType == "covr")
        {
            if (extractAlbumArt && pos + 16 <= end)
            {
                size_t dataStart = pos + 16;
                if (dataStart < end)
                {
                    size_t imageSize = atomSize - 16;
                    if (imageSize > 0 && imageSize < 10 * 1024 * 1024)
                    {
                        std::vector<uint8_t> imageData(data.begin() + dataStart, data.begin() + dataStart + imageSize);
                        track.SetAlbumArtData(imageData);
                        track.SetHasAlbumArt(true);
                    }
                }
            }
        }

        pos += atomSize;
    }

    return hasMetadata;
}

//==============================================================================
// Apple Metadata Atom Detection
//==============================================================================

bool Mp4MetadataParser::IsAppleMetaAtom(const std::string &atomType, const char *suffix) const
{
    return atomType.size() == 4 &&
           static_cast<unsigned char>(atomType[0]) == 0xA9 &&
           atomType[1] == suffix[0] &&
           atomType[2] == suffix[1] &&
           atomType[3] == suffix[2];
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t Mp4MetadataParser::ReadUInt32BE(const std::vector<uint8_t> &data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset]) << 24) |
           (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

uint16_t Mp4MetadataParser::ReadUInt16BE(const std::vector<uint8_t> &data, size_t offset) const
{
    if (offset + 2 > data.size()) return 0;
    return (static_cast<uint16_t>(data[offset]) << 8) |
           static_cast<uint16_t>(data[offset + 1]);
}

std::string Mp4MetadataParser::ReadString(const std::vector<uint8_t> &data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char *>(&data[offset]), length);
}

//==============================================================================
// String Utilities
//==============================================================================

std::string Mp4MetadataParser::CleanString(const std::string &input) const
{
    if (input.empty()) return "";

    std::string result;
    result.reserve(input.size());
    bool inSpace = false;

    for (char c : input)
    {
        if (c == '\0' || (c < 32 && c != '\n' && c != '\t' && c != '\r'))
            continue;

        if (std::isspace(static_cast<unsigned char>(c)))
        {
            if (!inSpace) { result.push_back(' '); inSpace = true; }
        }
        else
        {
            result.push_back(c);
            inSpace = false;
        }
    }

    size_t start = result.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = result.find_last_not_of(" \t\n\r");
    return result.substr(start, end - start + 1);
}

} // namespace moosic