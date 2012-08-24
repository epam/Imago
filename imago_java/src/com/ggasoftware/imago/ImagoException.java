/****************************************************************************
 * Copyright (C) 2011 GGA Software Services LLC
 *
 * This file is part of Imago toolkit.
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

package com.ggasoftware.imago;

public class ImagoException extends RuntimeException {

    public ImagoException() {
        super();
    }

   public ImagoException(String message) {
        super(message);
   }
}