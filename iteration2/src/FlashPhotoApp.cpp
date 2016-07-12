/*
FlashPhotoApp.cpp
Originally created by the CSci-3081W TAs

Modifed by 3081 Group App
"Iteration2"
Spring 2016
Alex Long - longx552
Steven Vande Hei - vand0850
Grant Knott - knott085
*/


#include "png.h"
#include "FlashPhotoApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <setjmp.h>
#include <stdio.h>
#include "jpeglib.h"

#include <cmath>

#include <iostream>

using std::cout;
using std::endl;

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

FlashPhotoApp::FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("FlashPhoto");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);

    initGlui();
    initGraphics();
}

void FlashPhotoApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

FlashPhotoApp::~FlashPhotoApp() {}


void FlashPhotoApp::mouseDragged(int x, int y)
{
    int max_steps = 40;

	// We implimented a smoothing feature by interpolating between
	// mouse events. This is at the expense of processing, though,
	// because we just "stamp" the tool many times between the two
	// even locations. you can reduce max_steps until it runs
	// smoothly on your machine.

	// Get the differences between the events
	// in each direction
	int delta_x = x-m_mouseLastX;
	int delta_y = y-m_mouseLastY;

	// Calculate the min number of steps necesary to fill
	// completely between the two event locations.
	float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
	int step_count = pixelsBetween;
	int step_size = 1;

	// Optimize by maxing out at the max_steps,
	// and fill evenly between
	if (pixelsBetween > max_steps)
	{
		step_size = pixelsBetween/max_steps;
		step_count = max_steps;
	}

	// Iterate between the event locations
	for (int i = 0; i < pixelsBetween; i+=step_size)
	{
		int x = m_mouseLastX+(i*delta_x/pixelsBetween);
		int y = m_mouseLastY+(i*delta_y/pixelsBetween);

		if(m_tools[m_curTool].get() == m_tools[1].get()) {
            ColorData backgroundColor;
            m_tools[m_curTool]->apply(x, m_height-y, m_displayBuffer.get(), backgroundColor);
		}
		else {
            m_tools[m_curTool]->apply(x, m_height-y, m_displayBuffer.get(), ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue));
		}
	}

	// let the previous point catch up with the current.
	m_mouseLastX = x;
	m_mouseLastY = y;

}

void FlashPhotoApp::mouseMoved(int x, int y)
{

}

void FlashPhotoApp::leftMouseDown(int x, int y)
{
    pushUndo();
    if(m_tools[m_curTool].get() == m_tools[1].get()) {
        ColorData backgroundColor;
        m_tools[m_curTool]->apply(x, m_height-y, m_displayBuffer.get(), backgroundColor);
    }
    else {
        m_tools[m_curTool]->apply(x, m_height-y, m_displayBuffer.get(), ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue));
    }

	m_mouseLastX = x;
	m_mouseLastY = y;
}

void FlashPhotoApp::leftMouseUp(int x, int y)
{
    std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void FlashPhotoApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer.reset(new PixelBuffer(width, height, backgroundColor));
}

void FlashPhotoApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
		new GLUI_RadioButton(radio, "Pen");
		m_tools[0].reset(new Pen());
		new GLUI_RadioButton(radio, "Eraser");
		m_tools[1].reset(new Eraser());
		new GLUI_RadioButton(radio, "Spray Can");
		m_tools[2].reset(new SprayCan());
		new GLUI_RadioButton(radio, "Calligraphy Pen");
		m_tools[3].reset(new CalligraphyPen());
		new GLUI_RadioButton(radio, "Highlighter");
		m_tools[4].reset(new Highlighter());
		new GLUI_RadioButton(radio, "Crayon");
		m_tools[5].reset(new Crayon());
        new GLUI_RadioButton(radio, "Stamp");
        m_tools[6].reset(new StampTool());
        new GLUI_RadioButton(radio, "Blur");
        m_tools[7].reset(new BlurTool());
    }

    GLUI_Panel *colorPanel = new GLUI_Panel(m_glui, "Tool Color");
    {
        m_curColorRed = 0;
        m_gluiControlHooks.spinnerRed  = new GLUI_Spinner(colorPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
        m_gluiControlHooks.spinnerRed->set_float_limits(0, 1.0);

        m_curColorGreen = 0;
        m_gluiControlHooks.spinnerGreen  = new GLUI_Spinner(colorPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
        m_gluiControlHooks.spinnerGreen->set_float_limits(0, 1.0);

        m_curColorBlue = 0;
        m_gluiControlHooks.spinnerBlue  = new GLUI_Spinner(colorPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
        m_gluiControlHooks.spinnerBlue->set_float_limits(0, 1.0);

        new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
        new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
        new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
        new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
        new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
        new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
        new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
        new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
    }

    // UNDO,REDO,QUIT
    {
        m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
        undoEnabled(false);
        m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
        redoEnabled(false);

        new GLUI_Separator(m_glui);
        new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
    }

    new GLUI_Column(m_glui, true);
    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
        {
            GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:", &m_filterParameters.blur_amount);
            filterBlurAmount->set_int_limits(0, 20);

            filterBlurAmount->set_int_val(5);

            new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
            m_convFilters[0].reset(new FBlur(&m_filterParameters.blur_amount));
        }

        GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
        {
            GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel, "Amount:", &m_filterParameters.motionBlur_amount);
            filterMotionBlurAmount->set_int_limits(0, 100);

            filterMotionBlurAmount->set_int_val(5);

            m_filterParameters.motionBlur_direction = 0;
            GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel, &m_filterParameters.motionBlur_direction);
            new GLUI_RadioButton(dirBlur, "North/South");
            new GLUI_RadioButton(dirBlur, "East/West");
            new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
            new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

            new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
            m_convFilters[1].reset(new FMotionBlur(&m_filterParameters.motionBlur_amount, &m_filterParameters.motionBlur_direction));
        }
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(0, 100);

            filterSharpAmount->set_int_val(5);

            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
            m_convFilters[2].reset(new FSharpen(&m_filterParameters.sharpen_amount));
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");
        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
            m_convFilters[3].reset(new FEdgeDetect());
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);

            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
            m_filters[0].reset(new FThreshold(&m_filterParameters.threshold_amount));
        }

		new GLUI_Column(filterPanel, true);

        GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
        {
            GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel, "Amount:", &m_filterParameters.saturation_amount);
            filterSaturationAmount->set_float_limits(-10, 10);
            filterSaturationAmount->set_float_val(1);

            new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
            m_filters[1].reset(new FSaturation(&m_filterParameters.saturation_amount));
        }

        GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(channelPanel, "Red:", &m_filterParameters.channel_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(channelPanel, "Green:", &m_filterParameters.channel_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(channelPanel, "Blue:", &m_filterParameters.channel_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
            m_filters[2].reset(new FChannels(&m_filterParameters.channel_colorRed, &m_filterParameters.channel_colorGreen, &m_filterParameters.channel_colorBlue));
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
            m_filters[3].reset(new FQuantize(&m_filterParameters.quantize_bins));
        }

        GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel, "Sepia"); // YOUR SPECIAL FILTER PANEL
        {

            new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_SPECIAL_FILTER, s_gluicallback);
            m_filters[4].reset(new FSepia());
        }
    }

    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);

        m_gluiControlHooks.fileBrowser->set_h(400);

        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);
        m_gluiControlHooks.loadStampButton = new GLUI_Button(imagePanel, "Load Stamp", UI_LOAD_STAMP_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);

        loadCanvasEnabled(false);
        loadStampEnabled(false);
        saveCanvasEnabled(false);
    }
    return;
}

void FlashPhotoApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_APPLY_BLUR:
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_DITHER:
            applyFilterThreshold();
            break;
        case UI_APPLY_SATURATE:
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_APPLY_SPECIAL_FILTER:
            applyFilterSpecial();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
            break;
        default:
            break;
    }

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}


// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how FlashPhotoApp should respond to the
// button presses.

PixelBuffer* load_png(const char *file_name, ColorData backgroundColor)  /* We need to open the file */
{
   png_structp png_ptr;
   png_infop info_ptr;
   int sig_read = 0;
   int bit_depth, color_type, interlace_type;
   png_bytep* row_pointers;
   FILE *fp;

   if ((fp = fopen(file_name, "rb")) == NULL)
   {
	  std::cout << "Failed to open file " << file_name << std::endl;
      return NULL;
   }
   /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also supply the
    * the compiler header file version, so that we know if the application
    * was compiled with a compatible version of the library.  REQUIRED
    */
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

   if (png_ptr == NULL)
   {
      fclose(fp);
	  std::cout << "Failed to png_structp png_ptr" << std::endl;
      return NULL;
   }

   /* Allocate/initialize the memory for image information.  REQUIRED. */
   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_read_struct(&png_ptr, NULL, NULL);
	  std::cout << "Failed to allocate memory of image information" << std::endl;
      return NULL;
   }

   /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      /* Free all of the memory associated with the png_ptr and info_ptr */
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);
      /* If we get here, we had a problem reading the file */
	  std::cout << "Failed to read file" << std::endl;
      return NULL;
   }

   /* Set up the input control if you are using standard C streams */
   png_init_io(png_ptr, fp);

   /* If we have already read some of the signature */
   png_set_sig_bytes(png_ptr, sig_read);

   /*
    * If you have enough memory to read in the entire image at once,
    * and you need to specify only transforms that can be controlled
    * with one of the PNG_TRANSFORM_* bits (this presently excludes
    * quantizing, filling, setting background, and doing gamma
    * adjustment), then you can read the entire image (including
    * pixels) into the info structure with this call:
    */
   png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_GRAY_TO_RGB, NULL);

   /* At this point you have read the entire image */
   row_pointers = png_get_rows(png_ptr, info_ptr);
   int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
   int height = png_get_image_height(png_ptr, info_ptr);
   int width = png_get_image_width(png_ptr, info_ptr);
   float red;
   float green;
   float blue;
   float alpha = 1.0;
   int num_channels = rowbytes / width;
   PixelBuffer* newImage = new PixelBuffer(width, height, backgroundColor);
   for(int i = 0; i < height; i++)
   {
		for(int j = 0; j < rowbytes; j += num_channels)
		{
			red = row_pointers[i][j] / (float) UCHAR_MAX;
			green = row_pointers[i][j+1] / (float) UCHAR_MAX;
			blue = row_pointers[i][j+2] / (float) UCHAR_MAX;
			if(num_channels == 4)
			{
				alpha = row_pointers[i][j+3] / (float) UCHAR_MAX;
			}
			newImage->setPixel((j / num_channels), height - i - 1, ColorData(red, green, blue, alpha));
		}
   }

   /* Clean up after the read, and free any memory allocated - REQUIRED */
   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

   /* Close the file */
   fclose(fp);

   /* That's it */
	return newImage;
}

void save_png(FlashPhotoApp* that)
{
   FILE *fp;
   png_structp png_ptr;
   png_infop info_ptr;

   /* Open the file */
   fp = fopen(that->m_fileName.c_str(), "wb");
   if (fp == NULL)
      return;

   /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also check that
    * the library version is compatible with the one used at compile time,
    * in case we are using dynamically linked libraries.  REQUIRED.
    */
   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

   if (png_ptr == NULL)
   {
      fclose(fp);
      return;
   }

   /* Allocate/initialize the image information data.  REQUIRED */
   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_write_struct(&png_ptr,  NULL);
      return;
   }

   /* Set error handling.  REQUIRED if you aren't supplying your own
    * error handling functions in the png_create_write_struct() call.
    */
   if (setjmp(png_jmpbuf(png_ptr)))
   {
      /* If we get here, we had a problem writing the file */
      fclose(fp);
      png_destroy_write_struct(&png_ptr, &info_ptr);
      return;
   }

   /* Set up the output control if you are using standard C streams */
   png_init_io(png_ptr, fp);

   int height = that->m_displayBuffer->getHeight();
   int width = that->m_displayBuffer->getWidth();

   png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

   /* Write the file header information.  REQUIRED */
   png_write_info(png_ptr, info_ptr);

   std::vector< png_bytep > row_pointers(height);
   std::vector< std::vector< png_byte > > image_data(height);

   /* Set up pointers into your "image" byte array */
   for(int i = 0; i < height; i++)
   {
	image_data[i].resize(width * 4);
	row_pointers[i] = image_data[i].data();
		for(int j = 0; j < (width * 4); j += 4)
		{
			ColorData pixel = that->m_displayBuffer->getPixel((j / 4), (height - i - 1)).clampedColor();
			row_pointers[i][j] = (png_byte) (pixel.getRed() * UCHAR_MAX);
			row_pointers[i][j+1] = (png_byte) (pixel.getGreen() * UCHAR_MAX);
			row_pointers[i][j+2] = (png_byte) (pixel.getBlue() * UCHAR_MAX);
			row_pointers[i][j+3] = (png_byte) (pixel.getAlpha() * UCHAR_MAX);
		}
   }

   png_write_image(png_ptr, row_pointers.data());
   png_write_end(png_ptr, info_ptr);

   /* Clean up after the write, and free any memory allocated */
   png_destroy_write_struct(&png_ptr, &info_ptr);

   /* Close the file */
   fclose(fp);

   /* That's it */
   return;
}

void save_jpeg(FlashPhotoApp* that)
{
  /* This struct contains the JPEG compression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   * It is possible to have several such structures, representing multiple
   * compression/decompression processes, in existence at once.  We refer
   * to any one struct (and its associated working data) as a "JPEG object".
   */
  struct jpeg_compress_struct cinfo;
  /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */

  /* Step 1: allocate and initialize JPEG compression object */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
   const char* fileName = that->m_fileName.c_str();
  if ((outfile = fopen(fileName, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", fileName);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = that->m_displayBuffer->getWidth(); 	/* image width and height, in pixels */
  cinfo.image_height = that->m_displayBuffer->getHeight();
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, 80, TRUE /* limit to baseline-JPEG values; quality = 80 out of 100 */);

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
  row_stride = that->m_displayBuffer->getWidth()* 3;	/* JSAMPLEs per row in image_buffer */
  std::vector< JSAMPLE > row_buffer(row_stride);
  int image_width = that->m_displayBuffer->getWidth();
  JSAMPLE red;
  JSAMPLE blue;
  JSAMPLE green;
  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    //row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
		//red = (buffer[0][i*3] / (float) MAXJSAMPLE);
		//green = (buffer[0][(i*3) + 1] / (float) MAXJSAMPLE);
		//blue = (buffer[0][(i*3) + 2] / (float) MAXJSAMPLE);
	for(int i = 0; i < image_width; i++)
	{
		//Calculate current pixel height by subtracting next_scanline from image_height and then subtracting 1 to fix off-by-one error
		ColorData pixel = that->m_displayBuffer->getPixel(i, cinfo.image_height - cinfo.next_scanline - 1).clampedColor();
		red = (JSAMPLE) (pixel.getRed() * (float) MAXJSAMPLE);
		blue = (JSAMPLE) (pixel.getBlue() * (float) MAXJSAMPLE);
		green = (JSAMPLE) (pixel.getGreen() * (float) MAXJSAMPLE);
		row_buffer[i*3] = red;
		row_buffer[(i*3) + 1] = green;
		row_buffer[(i*3) + 2] = blue;
	}
	row_pointer[0] = row_buffer.data();
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
	return;
}

PixelBuffer* load_jpeg(const char* fileName, ColorData backgroundColor)
{
	/* This struct contains the JPEG decompression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	*/
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	/* More stuff */
	FILE * infile;		/* source file */
	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */
	struct my_error_mgr jerr;
	/* In this example we want to open the input file before doing anything else,
	* so that the setjmp() error recovery below can assume the file is open.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to read binary files.
	*/

	if ((infile = fopen(fileName, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", fileName);
		return NULL;
	}

	/* Step 1: allocate and initialize JPEG decompression object */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return NULL;
	}
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */

	//Look in jdatasrc.c to see what's going on.
	jpeg_stdio_src(&cinfo, infile);

	/* Step 3: read file parameters with jpeg_read_header() */

	(void) jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	*   (a) suspension is not possible with the stdio data source, and
	*   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	* See libjpeg.txt for more info.
	*/

	/* Step 4: set parameters for decompression */

	/* In this example, we don't need to change any of the defaults set by
	* jpeg_read_header(), so we do nothing here.
	*/

	/* Step 5: Start decompressor */

	(void) jpeg_start_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	* In this example, we need to make an output work buffer of the right size.
	*/
	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;
	/* Make a one-row-high sample array that will go away when done with image */
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */

	/* Here we use the library's state variable cinfo.output_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	*/

	/* Create new PixelBuffer for new image */
	PixelBuffer* newImage = new PixelBuffer(cinfo.image_width, cinfo.image_height, backgroundColor);
	int image_row;
	float red;
	float blue;
	float green;

	while (cinfo.output_scanline < cinfo.output_height) {
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
		 * Here the array is only one element long, but you could ask for
		 * more than one scanline at a time if that's more convenient.
		 */
		 image_row = cinfo.output_scanline;
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		/* Assume put_scanline_someplace wants a pointer and sample count. */
		for(int i = 0; i < cinfo.image_width; i++)
		{
			//Color data for each pixel stored in buffer
			//Divided by MAXJSAMPLE to get value between 0.0 and 1.0
			red = (buffer[0][i*3] / (float) MAXJSAMPLE);
			green = (buffer[0][(i*3) + 1] / (float) MAXJSAMPLE);
			blue = (buffer[0][(i*3) + 2] / (float) MAXJSAMPLE);
			//Calculate y-coordinate by taking (new image height) - (currentscanline) which will cancel off-by-one error caused by subtracting canvas height
			newImage->setPixel(i, cinfo.image_height - cinfo.output_scanline, ColorData(red, green, blue));
		}
	}

	/* Step 7: Finish decompression */

	(void) jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* Step 8: Release JPEG decompression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	/* After finish_decompress, we can close the input file.
	* Here we postpone it until after no more JPEG errors are possible,
	* so as to simplify the setjmp error logic above.  (Actually, I don't
	* think that jpeg_destroy can do an error exit, but why assume anything...)
	*/
	fclose(infile);

	/* At this point you may want to check to see whether any corrupt-data
	* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	*/

	/* And we're done! */
	return newImage;
}

void FlashPhotoApp::loadImageToCanvas()
{
	PixelBuffer* newImage;
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    if (hasSuffix(m_fileName, ".png"))
	{
		newImage = load_png(m_fileName.c_str(), m_displayBuffer->getBackgroundColor());
	}
	else
	{
		newImage = load_jpeg(m_fileName.c_str(), m_displayBuffer->getBackgroundColor());
	}
	if (newImage == NULL)
	{
    		cout << "Failed to load file " << m_fileName << endl;
		return;
	}
	m_displayBuffer.reset(newImage);
    undo_buffer.clear();
    undoEnabled(false);
    redo_buffer.clear();
    redoEnabled(false);
	this->reshape(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());
	this->display();
}

void FlashPhotoApp::loadImageToStamp()
{
	PixelBuffer* newStampImage;
    cout << "Load Stamp has been clicked for file " << m_fileName << endl;
    if (hasSuffix(m_fileName, ".png"))
	{
		newStampImage = load_png(m_fileName.c_str(), m_displayBuffer->getBackgroundColor());
	}
	else
	{
		newStampImage = load_jpeg(m_fileName.c_str(), m_displayBuffer->getBackgroundColor());
	}
	if (newStampImage == NULL)
	{
    		cout << "Failed to load file " << m_fileName << endl;
		return;
	}
	static_cast<StampTool*>(m_tools[6].get())->setStamp(newStampImage);
}

void FlashPhotoApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    if (hasSuffix(m_fileName, ".png"))
	{
		save_png(this);
	}
	else
	{
		save_jpeg(this);
	}
	return;
}

void FlashPhotoApp::applyFilterThreshold()
{
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    pushUndo();
    m_filters[0]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterChannel()
{
    cout << "Apply has been clicked for Channels with red = " << m_filterParameters.channel_colorRed
    << ", green = " << m_filterParameters.channel_colorGreen
    << ", blue = " << m_filterParameters.channel_colorBlue << endl;
    pushUndo();
    m_filters[2]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturation_amount << endl;
    pushUndo();
    m_filters[1]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterBlur()
{
    cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
    pushUndo();
    m_convFilters[0]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    pushUndo();
    m_convFilters[2]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterMotionBlur()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.motionBlur_amount
    << " and direction " << m_filterParameters.motionBlur_direction << endl;
    pushUndo();
    m_convFilters[1]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    pushUndo();
    m_convFilters[3]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    pushUndo();
    m_filters[3]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::applyFilterSpecial() {
    cout << "Apply has been clicked for Special" << endl;
    pushUndo();
    m_filters[4]->apply(m_displayBuffer.get());
}

void FlashPhotoApp::pushUndo()
{
    if(undo_buffer.size() == MAX_UNDO_SIZE)
    {
        //remove oldest entry
        undo_buffer.pop_front();
    }
    redo_buffer.clear();
    redoEnabled(false);
    //create a copy of the current displayBuffer
    undo_buffer.emplace_back(new PixelBuffer(*m_displayBuffer));
    undoEnabled(true);
}

void FlashPhotoApp::undoOperation()
{
    cout << "Undoing..." << endl; 
    if(redo_buffer.size() == MAX_UNDO_SIZE)
    {
        //remove oldest entry
        redo_buffer.pop_front();
    }
    redo_buffer.emplace_back(std::move(m_displayBuffer));
    redoEnabled(true);
    m_displayBuffer = std::move(undo_buffer.back());
    undo_buffer.pop_back();
    if(undo_buffer.empty())
    {
        undoEnabled(false);
    }
    this->display();
}

void FlashPhotoApp::redoOperation()
{
    cout << "Redoing..." << endl;
    if(undo_buffer.size() == MAX_UNDO_SIZE)
    {
        //remove oldest entry
        undo_buffer.pop_front();
    }
    undo_buffer.emplace_back(std::move(m_displayBuffer));
    undoEnabled(true);
    m_displayBuffer = std::move(redo_buffer.back());
    redo_buffer.pop_back();
    if(redo_buffer.empty())
    {
        redoEnabled(false);
    }
    this->display();
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void FlashPhotoApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void FlashPhotoApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void FlashPhotoApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void FlashPhotoApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void FlashPhotoApp::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void FlashPhotoApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void FlashPhotoApp::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}

bool FlashPhotoApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


bool FlashPhotoApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool FlashPhotoApp::isValidImageFile(const std::string & name) {

    FILE *f;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }
    return isValid;
}

void FlashPhotoApp::setImageFile(const std::string & fileName)
{
    // If a directory was selected
    // instead of a file, use the
    // latest file typed or selected.
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }


    // TOGGLE SAVE FEATURE
    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.

    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }

    // TOGGLE LOAD FEATURE

    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (isValidImageFile(imageFile)) {
        loadStampEnabled(true);
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadStampEnabled(false);
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void FlashPhotoApp::initGraphics() {
	// Initialize OpenGL for 2D graphics as used in the BrushWork app
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glViewport(0, 0, m_width, m_height);
}
