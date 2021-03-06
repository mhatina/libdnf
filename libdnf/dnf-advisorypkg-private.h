/*
 * Copyright (C) 2014 Red Hat, Inc.
 * Copyright (C) 2015 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __DNF_ADVISORYPKG_PRIVATE_H
#define __DNF_ADVISORYPKG_PRIVATE_H

#include <glib-object.h>

#include "dnf-advisorypkg.h"

G_BEGIN_DECLS

DnfAdvisoryPkg  *dnf_advisorypkg_new            (void);
void             dnf_advisorypkg_set_name       (DnfAdvisoryPkg *advisorypkg,
                                                 const char     *value);
void             dnf_advisorypkg_set_evr        (DnfAdvisoryPkg *advisorypkg,
                                                 const char     *value);
void             dnf_advisorypkg_set_arch       (DnfAdvisoryPkg *advisorypkg,
                                                 const char     *value);
void             dnf_advisorypkg_set_filename   (DnfAdvisoryPkg *advisorypkg,
                                                 const char     *value);

G_END_DECLS

#endif /* __DNF_ADVISORYPKG_PRIVATE_H */
