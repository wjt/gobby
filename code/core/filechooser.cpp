/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008-2015 Armin Burgmeier <armin@arbur.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "core/filechooser.hpp"
#include "util/i18n.hpp"

#include <glibmm/miscutils.h>
#include <glibmm/convert.h>

Gobby::FileChooser::Dialog::Dialog(Gobby::FileChooser& chooser,
                                   Gtk::Window& parent,
                                   const Glib::ustring& title,
                                   Gtk::FileChooserAction action):
	Gtk::FileChooserNative(title, parent, action, "", ""),
	m_chooser(chooser)
{
	// TODO: the dialog prevents interaction with the parent window but Shell does not grey it out. If I toggle the 'modal' property on the dialog to false then true again with the inspector, it behaves as expected. Is this a Shell bug, a portal bug, or something else?
	set_modal(true);
	set_local_only(false);
	set_current_folder_uri(m_chooser.get_current_folder_uri());
}

Gobby::FileChooser::Dialog::~Dialog()
{
	m_chooser.set_current_folder_uri(get_current_folder_uri());
}

Gobby::FileChooser::FileChooser():
	m_current_folder_uri(Glib::filename_to_uri(Glib::get_current_dir()))
{
}

const std::string& Gobby::FileChooser::get_current_folder_uri() const
{
	return m_current_folder_uri;
}

void Gobby::FileChooser::set_current_folder_uri(const std::string& uri)
{
	m_current_folder_uri = uri;
}

