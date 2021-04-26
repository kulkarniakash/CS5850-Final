#ifndef GER
#define GER
#include <SDL_Headers.hpp>

//GraphicsEngineRenderer taken from Sumanth's assignment-2. Written by Shreyas Shivashankar.

/*!
 * @brief This class serves as an interface to the main graphics renderer for our engine.
 * taken from Sumanth's assignment-2. Written by Shreyas Shivashankar.
 */
class GraphicsEngineRenderer {
    public:
    /*!
     * @brief Constructor for GraphicsEngineRenderer
     * @param w: int represents the width of our width
     * @param h: int represents the height of our height
     */
    GraphicsEngineRenderer(int w, int h);
    /*!
     * Destructor
     */
    ~GraphicsEngineRenderer();
    /*!
     * @brief Set the color for the background whenever, the color is cleared.
     * @param r: int to represent the amount of red in the color
     * @param g: int to represent the amount of green in the color
     * @param b: int to represent the amount of blue in the color
     * @param a: int to represent how transparent the object is
     */
    void SetRenderDrawColor(int r, int g, int b, int a);
    
    //! @brief Clear the screen
    void RenderClear();
    
    //! @brief Render whatever is in the backbuffer to the screen.
    void RenderPresent();
    
    //! @return Get Pointer to Window
    SDL_Window* GetWindow();
    
    //! @return Get Pointer to Renderer
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
