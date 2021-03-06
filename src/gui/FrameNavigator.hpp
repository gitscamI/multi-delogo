/*
 * Copyright (C) 2018 Werner Turing <werner.turing@protonmail.com>
 *
 * This file is part of multi-delogo.
 *
 * multi-delogo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * multi-delogo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with multi-delogo.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MDL_FRAME_NAVIGATOR_H
#define MDL_FRAME_NAVIGATOR_H

#include <gtkmm.h>

#include "common/FrameProvider.hpp"

#include "NumericEntry.hpp"
#include "FrameView.hpp"


namespace mdl {
  class FrameNavigator : public Gtk::Grid
  {
  public:
    FrameNavigator(Gtk::Window& parent_window,
                   const Glib::RefPtr<FrameProvider>& frame_provider);

    int get_number_of_frames() const;
    double get_fps() const;
    void single_step_frame(int direction);
    void jump_step_frame(int direction);
    void change_displayed_frame(int new_frame_number);

    int get_jump_size() const;
    void set_jump_size(int jump_size);

    FrameView& get_frame_view();

    typedef sigc::signal<void, int> type_signal_frame_changed;
    type_signal_frame_changed signal_frame_changed();

  private:
    Gtk::Window& parent_window_;

    Glib::RefPtr<FrameProvider> frame_provider_;
    int number_of_frames_;
    int frame_number_;

    FrameView frame_view_;

    NumericEntry txt_frame_number_;
    NumericEntry txt_jump_size_;

    gdouble zoom_;
    Gtk::Label lbl_zoom_;
    Gtk::Button btn_zoom_out_;
    Gtk::Button btn_zoom_in_;
    Gtk::Button btn_zoom_100_;

    type_signal_frame_changed signal_frame_changed_;


    Gtk::Grid* create_navigation_box();
    Gtk::Grid* create_zoom_box();

    void on_frame_number_activate();
    bool on_frame_number_input(GdkEventFocus*);

    void on_step_zoom(gdouble increment);
    void on_zoom_100();
    void on_zoom_fit();
    void set_zoom(gdouble zoom);
  };
}

#endif // MDL_FRAME_NAVIGATOR_H
