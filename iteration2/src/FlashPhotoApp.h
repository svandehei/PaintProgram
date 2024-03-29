//
//  FlashPhotoApp.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef FLASHPHOTOAPP_H
#define FLASHPHOTOAPP_H

#include "BaseGfxApp.h"
#include "Tool.h"
#include "Pen.h"
#include "Crayon.h"
#include "SprayCan.h"
#include "CalligraphyPen.h"
#include "Highlighter.h"
#include "Eraser.h"
#include "Filter.h"
#include "FThreshold.h"
#include "FSaturation.h"
#include "FQuantize.h"
#include "FChannels.h"
#include "FSepia.h"
#include "FBlur.h"
#include "FMotionBlur.h"
#include "StampTool.h"
#include "FEdgeDetect.h"
#include "BlurTool.h"
#include "FSharpen.h"
#include <memory>
#include <deque>

#define MAX_UNDO_SIZE 50

class ColorData;
class PixelBuffer;

class FlashPhotoApp : public BaseGfxApp {
public:

    FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~FlashPhotoApp();

    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);

private:

    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_LOAD_STAMP_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_BLUR,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_DITHER,
        UI_APPLY_SATURATE,
        UI_APPLY_CHANNEL,
        UI_APPLY_QUANTIZE,
        UI_APPLY_MOTION_BLUR,
        UI_APPLY_SPECIAL_FILTER,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void loadStampEnabled(bool enabled);
    void updateColors();

    void loadImageToCanvas();
    void loadImageToStamp();
    void saveCanvasToFile();

    void applyFilterBlur();
    void applyFilterSharpen();
    void applyFilterMotionBlur();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterChannel();
    void applyFilterSaturate();
    void applyFilterQuantize();
    void applyFilterSpecial();

    void pushUndo();
    void undoOperation();
    void redoOperation();



    void initGlui();
    void initGraphics();
    void initializeBuffers(ColorData initialColor, int width, int height);

    enum UIMotionBlurDirections {
        DIR_N_S,
        DIR_E_W,
        DIR_NE_SW,
        DIR_NW_SE
    };

    struct {
        float channel_colorRed;
        float channel_colorGreen;
        float channel_colorBlue;
        float saturation_amount;
        float threshold_amount;
        float blur_amount;
        float sharpen_amount;
        float motionBlur_amount;
        int motionBlur_direction;
        int quantize_bins;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *loadStampButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;

        GLUI_Spinner *spinnerRed;
        GLUI_Spinner *spinnerGreen;
        GLUI_Spinner *spinnerBlue;



    } m_gluiControlHooks;


    // Previous mouse coordinates for interpolating mouse moves
    int m_mouseLastX, m_mouseLastY;

    // This is the pointer to the buffer where the display PixelBuffer is stored
    std::unique_ptr< PixelBuffer > m_displayBuffer;

    // These are used to store the selections from the GLUI user interface
    int m_curTool;
    float m_curColorRed, m_curColorGreen, m_curColorBlue;
    std::string m_fileName;  //Filename of canvas image
    std::deque< std::unique_ptr< PixelBuffer > > undo_buffer;
    std::deque< std::unique_ptr< PixelBuffer > > redo_buffer;
	std::unique_ptr<Tool> m_tools[8];
	std::unique_ptr<Filter> m_filters[5];
	std::unique_ptr<ConvolutionFilter> m_convFilters[4];

	friend void save_png(FlashPhotoApp* that);
	friend void save_jpeg(FlashPhotoApp* that);
};


#endif
