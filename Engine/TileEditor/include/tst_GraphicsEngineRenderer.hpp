#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP
// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
// Note that your path may be different depending on where you intalled things
//
//
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

//! @brief This class serves as an interface to the main graphics renderer for our engine.
class GraphicsEngineRenderer{
    public:
    
        /*!
         * @brief Constructor for GraphicsEngineRenderer
         * @param w: width of our renderer
         * @param h: height of our renderer
         */
        GraphicsEngineRenderer(int w, int h);
    
        //! @brief Destructor
        ~GraphicsEngineRenderer();
        /*!
         * @brief Sets the color of the background
         * @param r: value to show the amount of red
         * @param g: value to show the amount of green
         * @param b: value to show the amount of blue
         * @param a: value to show the amount of transparency
         */
    
        void SetRenderDrawColor(int r, int g, int b, int a);
    
        //! @brief Clears the screen
        void RenderClear();
    
        //! @brief Render whatever is in the backbuffer to the screen.
        void RenderPresent();
    
        //! @brief Get Pointer to Window
        SDL_Window* GetWindow();
    
        //! @brief Get Pointer to Renderer
        SDL_Renderer* GetRenderer();

    private:
        // Screen dimension constants
		int m_screenHeight;
		int m_screenWidth;
        // SDL Window
        SDL_Window* m_window;
        // SDL Renderer
        SDL_Renderer* m_renderer = nullptr;
};

#endif
