#include "ImageLoader.h"
#include <iostream>
#include <cstring>

// STB Image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// STB Image Resize (old version - simpler)
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

// For ImGui texture creation
#include <imgui.h>
#include <SDL.h>

namespace moosic
{

    ImageData ImageLoader::LoadFromFile(const std::filesystem::path &filePath)
    {
        ImageData result;

        int width, height, channels;
        unsigned char *data = stbi_load(
            filePath.string().c_str(),
            &width,
            &height,
            &channels,
            0);

        if (!data)
        {
            std::cout << "[ImageLoader] Failed to load: " << filePath.string() << "\n";
            return result;
        }

        result.width = width;
        result.height = height;
        result.channels = channels;

        size_t size = static_cast<size_t>(width) * height * channels;
        result.data.resize(size);
        memcpy(result.data.data(), data, size);

        stbi_image_free(data);

        return result;
    }

    ImageData ImageLoader::LoadFromMemory(const unsigned char *data, size_t size)
    {
        ImageData result;

        int width, height, channels;
        unsigned char *imgData = stbi_load_from_memory(
            data,
            static_cast<int>(size),
            &width,
            &height,
            &channels,
            0);

        if (!imgData)
        {
            std::cout << "[ImageLoader] Failed to load from memory\n";
            return result;
        }

        result.width = width;
        result.height = height;
        result.channels = channels;

        size_t dataSize = static_cast<size_t>(width) * height * channels;
        result.data.resize(dataSize);
        memcpy(result.data.data(), imgData, dataSize);

        stbi_image_free(imgData);

        return result;
    }
    ImageData ImageLoader::ToRGBA(const ImageData &image)
    {
        if (image.channels == 4)
            return image;

        ImageData result;
        result.width = image.width;
        result.height = image.height;
        result.channels = 4;

        size_t pixelCount = static_cast<size_t>(image.width) * image.height;
        result.data.resize(pixelCount * 4);

        // Manual RGB to RGBA conversion (no resize needed, same dimensions)
        const unsigned char *src = image.data.data();
        unsigned char *dst = result.data.data();

        for (size_t i = 0; i < pixelCount; ++i)
        {
            dst[0] = src[0]; // R
            dst[1] = src[1]; // G
            dst[2] = src[2]; // B
            dst[3] = 255;    // A (fully opaque)

            src += image.channels;
            dst += 4;
        }

        return result;
    }

    ImageData ImageLoader::Resize(const ImageData &image, int targetWidth, int targetHeight)
    {
        if (image.data.empty() || image.width <= 0 || image.height <= 0)
            return image;

        ImageData result;
        result.width = targetWidth;
        result.height = targetHeight;
        result.channels = image.channels;

        size_t size = static_cast<size_t>(targetWidth) * targetHeight * image.channels;
        result.data.resize(size);

        // Simple old API
        stbir_resize_uint8(
            image.data.data(),
            image.width,
            image.height,
            0,
            result.data.data(),
            targetWidth,
            targetHeight,
            0,
            image.channels);

        return result;
    }

    void *ImageLoader::CreateImGuiTexture(SDL_Renderer *renderer, const ImageData &image)
    {
        if (!renderer)
        {
            std::cout << "[ImageLoader] No renderer provided\n";
            return nullptr;
        }

        if (image.data.empty() || image.width <= 0 || image.height <= 0)
            return nullptr;

        // Convert to RGBA if needed
        ImageData rgba = ToRGBA(image);

        if (rgba.data.empty())
            return nullptr;

        // Create SDL texture from RGBA data
        SDL_Texture *texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STATIC,
            rgba.width,
            rgba.height);

        if (!texture)
        {
            std::cout << "[ImageLoader] Failed to create SDL texture: " << SDL_GetError() << "\n";
            return nullptr;
        }

        // Upload pixel data
        int result = SDL_UpdateTexture(
            texture,
            nullptr,
            rgba.data.data(),
            rgba.width * 4 // pitch = width * bytes per pixel (4 for RGBA)
        );

        if (result != 0)
        {
            std::cout << "[ImageLoader] Failed to update texture: " << SDL_GetError() << "\n";
            SDL_DestroyTexture(texture);
            return nullptr;
        }

        // Set texture blend mode for transparency
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        return reinterpret_cast<void *>(texture);
    }

    void ImageLoader::DestroyImGuiTexture(void *textureId)
    {
        if (!textureId)
            return;

        SDL_Texture *texture = static_cast<SDL_Texture *>(textureId);
        SDL_DestroyTexture(texture);
    }

    ImageData ImageLoader::ResizePixelArt(const ImageData &image, int targetWidth, int targetHeight, bool useNearest)
    {
        if (image.data.empty() || image.width <= 0 || image.height <= 0)
            return image;

        // For pixel art, use integer scaling to keep pixels sharp
        float scaleX = (float)targetWidth / image.width;
        float scaleY = (float)targetHeight / image.height;

        // If using nearest neighbor, round to nearest integer for pixel-perfect scaling
        if (useNearest)
        {
            // Find the best integer scale that fits within target dimensions
            int scale = std::max(1, (int)std::floor(std::min(scaleX, scaleY)));
            int newWidth = image.width * scale;
            int newHeight = image.height * scale;

            // If we can fit a larger integer scale, use it
            while ((image.width * (scale + 1) <= targetWidth) &&
                   (image.height * (scale + 1) <= targetHeight))
            {
                scale++;
            }

            targetWidth = image.width * scale;
            targetHeight = image.height * scale;
        }

        ImageData result;
        result.width = targetWidth;
        result.height = targetHeight;
        result.channels = image.channels;

        size_t size = static_cast<size_t>(targetWidth) * targetHeight * image.channels;
        result.data.resize(size);

        // Use STB resize with different filtering
        if (useNearest)
        {
            // STB doesn't have built-in nearest neighbor, so we do it manually
            // This maintains pixel art sharpness
            const unsigned char *src = image.data.data();
            unsigned char *dst = result.data.data();
            int channels = image.channels;

            for (int y = 0; y < targetHeight; y++)
            {
                for (int x = 0; x < targetWidth; x++)
                {
                    int srcX = (x * image.width) / targetWidth;
                    int srcY = (y * image.height) / targetHeight;

                    const unsigned char *srcPixel = src + (srcY * image.width + srcX) * channels;
                    unsigned char *dstPixel = dst + (y * targetWidth + x) * channels;

                    for (int c = 0; c < channels; c++)
                    {
                        dstPixel[c] = srcPixel[c];
                    }
                }
            }
        }
        else
        {
            // Standard bilinear resize (smoother, but blurs pixel art)
            stbir_resize_uint8(
                image.data.data(),
                image.width,
                image.height,
                0,
                result.data.data(),
                targetWidth,
                targetHeight,
                0,
                image.channels);
        }

        return result;
    }

} // namespace moosic