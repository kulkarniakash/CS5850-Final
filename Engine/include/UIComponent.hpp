#include <SDL_Headers.hpp>
#include "string"

class UIComponent {
    public:
    UIComponent(std::string fontPath, SDL_Rect src, std::string displayText, int fontSize);

    void render();

    void update(std::string text);

    private:
    SDL_Rect* m_textRect;
    SDL_Color White;
    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    SDL_Renderer * m_renderer;
    TTF_Font* m_displayFont;
};