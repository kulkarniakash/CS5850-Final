#include <SDL_Headers.hpp>
#include "string"

class UIComponent {
    public:
        /*!
        * @brief constructs a UIComponent
        * @param fontPath: String form of the path for the ttf file (font).
        * @param dest: SDL_Rect that determines the position the UIComponent should be rendered to.
        * @param displayText: string that represents the text to be rendered as a UI text.
        * @param fontSize: font size as an int.
        */
        UIComponent(std::string fontPath, SDL_Rect dest, std::string displayText, int fontSize);

        //! @brief Render the UIComponent to the renderer.
        void render();

        /*!
        * @brief Update the UIComponent's text with the given string's text
        * @param text: The string to set the UIComponent's text.
        */
        void update(std::string text);

    private:
        SDL_Rect m_textRect;
        SDL_Color White;
        SDL_Surface * m_surface;
        SDL_Texture * m_texture;
        SDL_Renderer * m_renderer;
        TTF_Font* m_displayFont;
};