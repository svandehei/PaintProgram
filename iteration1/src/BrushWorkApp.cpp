//
//  BrushWorkApp.cpp
//  Originally created by the CSci-3081W TAs.
//


#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

BrushWorkApp::BrushWorkApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : 
	BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50) {
	// Set the name of the window
	setCaption("BrushWork");
		
	// Initialize Interface
	initializeBuffers(backgroundColor, width, height);
	
	initGlui();
	initGraphics();
}

void BrushWorkApp::display() {
	drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}



BrushWorkApp::~BrushWorkApp() {
	if (m_displayBuffer) {
		delete m_displayBuffer;
	}
}


void BrushWorkApp::mouseDragged(int x, int y) {
	Tool* curTool = m_tools[m_curTool].get();
	//Apply the current tool here

	//if eraser, use background color
	if(curTool == m_tools[1].get()) {
	  ColorData backgroundColor;
	  y = m_height - y; //correct y axis pixel application
	  curTool->apply(x, y, m_displayBuffer, backgroundColor);
	  this->display();
	}
	
	//otherwise, set colors to current color
	else {  
	  ColorData newColors = ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue);
	  y = m_height - y; //correct y axis pixel application
	  curTool->apply(x, y, m_displayBuffer, newColors);
	  this->display();
	}
}

void BrushWorkApp::mouseMoved(int x, int y) {
	
}


void BrushWorkApp::leftMouseDown(int x, int y) {
	std::cout << "mousePressed " << x << " " << y << std::endl;
}

void BrushWorkApp::leftMouseUp(int x, int y) {
	std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void BrushWorkApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
	m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void BrushWorkApp::initGlui() {
	// Select first tool (this activates the first radio button in glui)
	m_curTool = 0;
	
	GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
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
	
	GLUI_Panel *colPanel = new GLUI_Panel(m_glui, "Tool Color");
	
	m_curColorRed = 0;
	m_spinnerR  = new GLUI_Spinner(colPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
	m_spinnerR->set_float_limits(0, 1.0);
	
	m_curColorGreen = 0;
	m_spinnerG  = new GLUI_Spinner(colPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
	m_spinnerG->set_float_limits(0, 1.0);
	
	m_curColorBlue = 0;
	m_spinnerB  = new GLUI_Spinner(colPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
	m_spinnerB->set_float_limits(0, 1.0);
	new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
	new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
	new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
	new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
	new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
	new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
	new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
	new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
	
	
	new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
}


void BrushWorkApp::initGraphics() {
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



void BrushWorkApp::gluiControl(int controlID) {
	switch (controlID) {
		case UI_PRESET_RED:
			m_curColorRed = 1;
			m_curColorGreen = 0;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_ORANGE:
			m_curColorRed = 1;
			m_curColorGreen = 0.5;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_YELLOW:
			m_curColorRed = 1;
			m_curColorGreen = 1;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_GREEN:
			m_curColorRed = 0;
			m_curColorGreen = 1;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_BLUE:
			m_curColorRed = 0;
			m_curColorGreen = 0;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_PURPLE:
			m_curColorRed = 0.5;
			m_curColorGreen = 0;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_WHITE:
			m_curColorRed = 1;
			m_curColorGreen = 1;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_BLACK:
			m_curColorRed = 0;
			m_curColorGreen = 0;
			m_curColorBlue = 0;
			break;
		default:
			break;
	}
	
	m_spinnerB->set_float_val(m_curColorBlue);
	m_spinnerG->set_float_val(m_curColorGreen);
	m_spinnerR->set_float_val(m_curColorRed);	
}
