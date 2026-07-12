//==============================================================================
// Mp4MetadataParser.cpp
//==============================================================================
// Custom binary parser for MP4/M4A metadata (iTunes atoms, cover art)
//==============================================================================

#include "Mp4MetadataParser.h"

namespace moosic
{

    //==============================================================================
    // Main Parse API
    //==============================================================================

    bool Mp4MetadataParser::Parse(const std::string &filePath, MusicTrack &track) const
    {
        auto data = ReadFileBytes(filePath);
        if (data.size() < 8)
            return false;

        return ParseAtoms(data, track);
    }

    //==============================================================================
    // Atom Tree Parser
    //==============================================================================

    bool Mp4MetadataParser::ParseAtoms(const std::vector<uint8_t> &data, MusicTrack &track) const
    {
        // Use a stack to avoid recursion
        std::vector<std::pair<size_t, size_t>> atomStack; // offset, size pairs
        atomStack.push_back({0, data.size()});

        bool hasMetadata = false;

        while (!atomStack.empty())
        {
            auto [parentOffset, parentEnd] = atomStack.back();
            atomStack.pop_back();

            size_t offset = parentOffset;
            size_t end = parentEnd;

            while (offset + 8 <= end)
            {
                uint32_t atomSize = ReadUInt32BE(data, offset);
                std::string atomType = ReadString(data, offset + 4, 4);

                if (atomSize < 8)
                    break; // Invalid atom size
                if (offset + atomSize > end)
                    break;

                if (atomType == "moov" || atomType == "udta")
                {
                    // Push container to stack instead of recursing
                    atomStack.push_back({offset + 8, offset + atomSize});
                }
                else if (atomType == "meta" && offset + 12 <= end)
                {
                    hasMetadata |= ParseMetaAtom(data, offset + 8, atomSize - 8, track);
                }
                else if (atomType == "ilst")
                {
                    hasMetadata |= ParseILST(data, offset + 8, atomSize - 8, track);
                }

                offset += atomSize;
            }
        }

        return hasMetadata;
    }

    //==============================================================================
    // Meta Atom (contains ilst)
    //==============================================================================

    bool Mp4MetadataParser::ParseMetaAtom(const std::vector<uint8_t> &data, size_t offset, size_t length, MusicTrack &track) const
    {
        // Skip 4-byte version/flags
        return ParseILST(data, offset + 4, length - 4, track);
    }

    //==============================================================================
    // iTunes Metadata List Parser
    //==============================================================================

    bool Mp4MetadataParser::ParseILST(const std::vector<uint8_t> &data, size_t offset, size_t length, MusicTrack &track) const
    {
        size_t end = offset + length;
        bool hasMetadata = false;

        while (offset + 8 <= end)
        {
            uint32_t atomSize = ReadUInt32BE(data, offset);
            std::string atomType = ReadString(data, offset + 4, 4);

            if (atomSize == 0 || atomSize > end - offset)
                break;

            //------------------------------------------------------------------
            // Title: ©nam or titl
            //------------------------------------------------------------------
            if (IsAppleMetaAtom(atomType, "nam") || atomType == "titl")
            {
                if (offset + 16 <= end)
                {
                    uint16_t valueLength = ReadUInt16BE(data, offset + 14);
                    if (offset + 16 + valueLength <= end)
                    {
                        track.SetTitle(CleanString(ReadString(data, offset + 16, valueLength)));
                        hasMetadata = true;
                    }
                }
            }
            //------------------------------------------------------------------
            // Artist: ©ART or "art "
            //------------------------------------------------------------------
            else if (IsAppleMetaAtom(atomType, "ART") || (atomType.size() == 4 && atomType[0] == 'a' && atomType[1] == 'r' && atomType[2] == 't' && atomType[3] == ' '))
            {
                if (offset + 16 <= end)
                {
                    uint16_t valueLength = ReadUInt16BE(data, offset + 14);
                    if (offset + 16 + valueLength <= end)
                    {
                        track.SetArtist(CleanString(ReadString(data, offset + 16, valueLength)));
                        hasMetadata = true;
                    }
                }
            }
            //------------------------------------------------------------------
            // Album: ©alb or albm
            //------------------------------------------------------------------
            else if (IsAppleMetaAtom(atomType, "alb") || atomType == "albm")
            {
                if (offset + 16 <= end)
                {
                    uint16_t valueLength = ReadUInt16BE(data, offset + 14);
                    if (offset + 16 + valueLength <= end)
                        track.SetAlbum(CleanString(ReadString(data, offset + 16, valueLength)));
                }
            }
            //------------------------------------------------------------------
            // Genre: ©gen or gnre
            //------------------------------------------------------------------
            else if (IsAppleMetaAtom(atomType, "gen") || atomType == "gnre")
            {
                if (offset + 16 <= end)
                {
                    uint16_t valueLength = ReadUInt16BE(data, offset + 14);
                    if (offset + 16 + valueLength <= end)
                        track.SetGenre(CleanString(ReadString(data, offset + 16, valueLength)));
                }
            }
            //------------------------------------------------------------------
            // Year: ©day or "day "
            //------------------------------------------------------------------
            else if (IsAppleMetaAtom(atomType, "day") || (atomType.size() == 4 && atomType[0] == 'd' && atomType[1] == 'a' && atomType[2] == 'y' && atomType[3] == ' '))
            {
                if (offset + 16 <= end)
                {
                    uint16_t valueLength = ReadUInt16BE(data, offset + 14);
                    if (offset + 16 + valueLength <= end)
                    {
                        try
                        {
                            track.SetYear(std::stoi(ReadString(data, offset + 16, valueLength)));
                        }
                        catch (...)
                        {
                        }
                    }
                }
            }
            //------------------------------------------------------------------
            // Track number: trkn
            //------------------------------------------------------------------
            else if (atomType == "trkn")
            {
                if (offset + 24 <= end)
                    track.SetTrackNumber(ReadUInt32BE(data, offset + 20));
            }
            //------------------------------------------------------------------
            // Cover art: covr
            //------------------------------------------------------------------
            else if (atomType == "covr")
            {
                if (offset + 16 <= end)
                {
                    size_t dataStart = offset + 16;
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

            offset += atomSize;
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
        if (offset + 4 > data.size())
            return 0;
        return (static_cast<uint32_t>(data[offset]) << 24) |
               (static_cast<uint32_t>(data[offset + 1]) << 16) |
               (static_cast<uint32_t>(data[offset + 2]) << 8) |
               static_cast<uint32_t>(data[offset + 3]);
    }

    uint16_t Mp4MetadataParser::ReadUInt16BE(const std::vector<uint8_t> &data, size_t offset) const
    {
        if (offset + 2 > data.size())
            return 0;
        return (static_cast<uint16_t>(data[offset]) << 8) |
               static_cast<uint16_t>(data[offset + 1]);
    }

    std::string Mp4MetadataParser::ReadString(const std::vector<uint8_t> &data, size_t offset, size_t length) const
    {
        if (offset + length > data.size())
            return "";
        return std::string(reinterpret_cast<const char *>(&data[offset]), length);
    }

    //==============================================================================
    // File I/O
    //==============================================================================

    std::vector<uint8_t> Mp4MetadataParser::ReadFileBytes(const std::string &filePath) const
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file.is_open())
            return {};

        std::streamsize size = file.tellg();
        if (size <= 0 || size > 100 * 1024 * 1024)
            return {};

        file.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(static_cast<size_t>(size));

        if (!file.read(reinterpret_cast<char *>(buffer.data()), size))
            return {};

        return buffer;
    }

    //==============================================================================
    // String Utilities
    //==============================================================================

    std::string Mp4MetadataParser::CleanString(const std::string &input) const
    {
        if (input.empty())
            return "";

        std::string result;
        result.reserve(input.size());
        bool inSpace = false;

        for (char c : input)
        {
            if (c == '\0' || (c < 32 && c != '\n' && c != '\t' && c != '\r'))
                continue;

            if (std::isspace(static_cast<unsigned char>(c)))
            {
                if (!inSpace)
                {
                    result.push_back(' ');
                    inSpace = true;
                }
            }
            else
            {
                result.push_back(c);
                inSpace = false;
            }
        }

        size_t start = result.find_first_not_of(" \t\n\r");
        if (start == std::string::npos)
            return "";
        size_t end = result.find_last_not_of(" \t\n\r");
        return result.substr(start, end - start + 1);
    }

} // namespace moosic