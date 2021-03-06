// generated by Fast Light User Interface Designer (fluid) version 2.1000

#ifndef widget_panel_h
#define widget_panel_h
#include <fltk/Window.h>
#include <fltk/Window.h>
extern gnui::Window* widgetbin_panel;
#include <fltk/Group.h>
#include <fltk/Button.h>
extern void type_make_cb(gnui::Button*, void*);
gnui::Window* make_widgetbin();
void type_make_cb(gnui::Widget*w,void*d);
#include <fltk/TabGroup.h>
extern void propagate_tabs(gnui::TabGroup*, void*);
extern gnui::TabGroup* panel_tabs;
extern void propagate_group(gnui::Group*, void*);
extern gnui::Group* gInput;
#include <fltk/Input.h>
extern void user_class_cb(gnui::Input*, void*);
#include <fltk/Choice.h>
extern void subtype_cb(gnui::Choice*, void*);
extern void label_cb(gnui::Input*, void*);
extern gnui::Group* gAlignment;
#include <fltk/CheckButton.h>
extern void image_inlined_cb(gnui::CheckButton*, void*);
extern gnui::CheckButton* include_image_button;
#include <fltk/Widget.h>
extern void align_cb(gnui::Button*, void*);
extern gnui::Widget* image_label;
extern void image_cb(gnui::Button*, void*);
extern gnui::Button* image_button;
extern gnui::Group* gDimensions;
#include <fltk/ValueInput.h>
extern void x_cb(gnui::ValueInput*, void*);
extern gnui::ValueInput* widget_x;
extern void y_cb(gnui::ValueInput*, void*);
extern gnui::ValueInput* widget_y;
extern void width_cb(gnui::ValueInput*, void*);
extern gnui::ValueInput* widget_w;
extern void height_cb(gnui::ValueInput*, void*);
extern gnui::ValueInput* widget_h;
extern void set_xy_cb(gnui::CheckButton*, void*);
extern gnui::CheckButton* set_xy;
extern void slider_size_cb(gnui::ValueInput*, void*);
extern gnui::Group* gValues;
extern void value_cb(gnui::ValueInput*, void*);
extern void min_cb(gnui::ValueInput*, void*);
extern void max_cb(gnui::ValueInput*, void*);
extern void step_cb(gnui::ValueInput*, void*);
extern void line_cb(gnui::ValueInput*, void*);
extern gnui::Group* gAttributes;
extern void visible_cb(gnui::CheckButton*, void*);
extern void active_cb(gnui::CheckButton*, void*);
extern void resizable_cb(gnui::CheckButton*, void*);
extern void hotspot_cb(gnui::CheckButton*, void*);
extern void border_cb(gnui::CheckButton*, void*);
extern void modal_cb(gnui::CheckButton*, void*);
extern void non_modal_cb(gnui::CheckButton*, void*);
#include <fltk/InvisibleBox.h>
#include "Shortcut_Button.h"
extern void shortcut_in_cb(Shortcut_Button*, void*);
#include <fltk/WordwrapInput.h>
extern void tooltip_cb(gnui::WordwrapInput*, void*);
extern void box_cb(gnui::Choice*, void*);
#include <fltk/LightButton.h>
extern void color_cb(gnui::LightButton*, void*);
extern void text_color_cb(gnui::LightButton*, void*);
extern void selection_color_cb(gnui::LightButton*, void*);
extern void selected_text_color_cb(gnui::LightButton*, void*);
extern void button_box_cb(gnui::Choice*, void*);
extern void button_color_cb(gnui::LightButton*, void*);
extern void label_color_cb(gnui::LightButton*, void*);
extern void highlight_color_cb(gnui::LightButton*, void*);
extern void highlight_label_color_cb(gnui::LightButton*, void*);
extern void label_style_cb(gnui::Choice*, void*);
extern void label_font_cb(gnui::Choice*, void*);
extern void label_size_cb(gnui::ValueInput*, void*);
extern void text_font_cb(gnui::Choice*, void*);
extern void text_size_cb(gnui::ValueInput*, void*);
extern void default_cb(gnui::Button*, void*);
extern void name_cb(gnui::Input*, void*);
extern void name_public_cb(gnui::CheckButton*, void*);
#include <fltk/MultiLineInput.h>
extern void extra_code_input_cb(gnui::MultiLineInput*, void*);
extern gnui::MultiLineInput* extra_code_input;
extern void callback_cb(gnui::MultiLineInput*, void*);
extern void user_data_cb(gnui::Input*, void*);
extern void when_cb(gnui::Choice*, void*);
extern void user_data_type_cb(gnui::Input*, void*);
extern bool overlays_invisible;
extern void overlay_cb(gnui::CheckButton*, void*);
extern gnui::CheckButton* overlaybutton;
#include <fltk/ReturnButton.h>
extern void ok_cb(gnui::ReturnButton*, void*);
extern void cancel_cb(gnui::Button*, void*);
extern void live_mode_cb(gnui::LightButton*, void*);
extern gnui::LightButton* wLiveMode;
gnui::Window* make_widget_panel();
#endif
