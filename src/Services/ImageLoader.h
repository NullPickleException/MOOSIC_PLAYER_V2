#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <cstdint>

struct SDL_Texture;
struct SDL_Renderer;

namespace moosic
{

    struct ImageData
    {
        std::vector<unsigned char> data; // RGBA pixel data
        int width = 0;
        int height = 0;
        int channels = 0;
    };

    class ImageLoader
    {
    public:
        ImageLoader() = default;
        ~ImageLoader() = default;

        // Load image from file
        ImageData LoadFromFile(const std::filesystem::path &filePath);

        // Load image from memory (for album art from FFmpeg)
        ImageData LoadFromMemory(const unsigned char *data, size_t size);

        // Resize image to target dimensions
        ImageData Resize(const ImageData &image, int targetWidth, int targetHeight);

        // Convert to RGBA (if not already)
        ImageData ToRGBA(const ImageData &image);

        // Get SDL texture for ImGui (requires renderer)
        void *CreateImGuiTexture(SDL_Renderer *renderer, const ImageData &image);
        void DestroyImGuiTexture(void *textureId);

        // In ImageLoader.h
        ImageData ResizePixelArt(const ImageData &image, int targetWidth, int targetHeight, bool useNearest = true);

    private:
        std::vector<unsigned char> m_textureData;
    };

} // namespace moosic