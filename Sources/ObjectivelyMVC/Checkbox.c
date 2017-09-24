/*
 * ObjectivelyMVC: MVC framework for OpenGL and SDL2 in c.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <assert.h>

#include <ObjectivelyMVC/Checkbox.h>

#define _Class _Checkbox

static Image *_check;
static const unsigned char _checkData[] = {
	0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
	0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20,
	0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7a, 0x7a, 0xf4, 0x00, 0x00, 0x00,
	0x06, 0x62, 0x4b, 0x47, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9,
	0x43, 0xbb, 0x7f, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00,
	0x00, 0x0b, 0x13, 0x00, 0x00, 0x0b, 0x13, 0x01, 0x00, 0x9a, 0x9c, 0x18,
	0x00, 0x00, 0x00, 0x07, 0x74, 0x49, 0x4d, 0x45, 0x07, 0xe0, 0x01, 0x14,
	0x02, 0x2f, 0x21, 0x65, 0x7a, 0xa4, 0x07, 0x00, 0x00, 0x00, 0x1d, 0x69,
	0x54, 0x58, 0x74, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x6e, 0x74, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x20, 0x77,
	0x69, 0x74, 0x68, 0x20, 0x47, 0x49, 0x4d, 0x50, 0x64, 0x2e, 0x65, 0x07,
	0x00, 0x00, 0x01, 0xcc, 0x49, 0x44, 0x41, 0x54, 0x58, 0xc3, 0xc5, 0xd7,
	0x3d, 0x68, 0x14, 0x51, 0x14, 0xc5, 0xf1, 0x3b, 0x71, 0x0d, 0xda, 0x44,
	0x62, 0x21, 0x5a, 0x29, 0xda, 0x88, 0xda, 0x68, 0x20, 0x4d, 0xb0, 0x4a,
	0xa1, 0x8d, 0x6c, 0x40, 0xed, 0xd3, 0x0a, 0xc1, 0x22, 0x8d, 0xb6, 0x62,
	0xa5, 0x8d, 0x95, 0x85, 0x85, 0xd8, 0x18, 0xc4, 0xc6, 0xca, 0x52, 0x0d,
	0x0a, 0x56, 0x22, 0x5a, 0x28, 0x2a, 0x22, 0x12, 0xfc, 0x00, 0xa3, 0xa0,
	0x22, 0x88, 0x1f, 0xc9, 0xfe, 0x2c, 0xbc, 0x81, 0x47, 0x08, 0xb8, 0x09,
	0xbb, 0xcf, 0xd7, 0x0c, 0x0c, 0xcc, 0xfb, 0xdf, 0x7b, 0xde, 0x99, 0x7b,
	0x66, 0x22, 0xfe, 0xf3, 0x6a, 0x6a, 0xc2, 0xd0, 0x8a, 0x88, 0xad, 0x11,
	0xb1, 0x10, 0x11, 0x1f, 0x9b, 0xa6, 0x59, 0xac, 0x05, 0x0e, 0xac, 0xc3,
	0x24, 0x6e, 0x61, 0x06, 0x7b, 0xd1, 0x54, 0x81, 0xe7, 0xf5, 0x30, 0x5e,
	0xf9, 0xbb, 0x3e, 0xe0, 0x50, 0x95, 0x02, 0x12, 0xbe, 0x3d, 0x3b, 0xef,
	0x64, 0x01, 0xb7, 0xb1, 0xab, 0x16, 0x7c, 0x10, 0xe7, 0xf0, 0x23, 0xe1,
	0xef, 0x71, 0xac, 0x54, 0xa7, 0xdf, 0xd2, 0x4f, 0xe0, 0x5d, 0xc2, 0x7f,
	0xe2, 0x3c, 0x06, 0x6b, 0x75, 0xbf, 0x13, 0xb3, 0x85, 0xf4, 0xb3, 0xd8,
	0x51, 0x0b, 0xbe, 0x11, 0x17, 0xb2, 0x6b, 0x78, 0x8b, 0x89, 0x9a, 0xd2,
	0x4f, 0x62, 0x3e, 0xe1, 0xdf, 0x71, 0x16, 0xeb, 0x6b, 0xbd, 0x72, 0x07,
	0xf0, 0x28, 0xe1, 0x8b, 0xb8, 0x89, 0x6d, 0xb5, 0xa4, 0x1f, 0xce, 0x41,
	0xb3, 0x90, 0x05, 0x3c, 0xc7, 0x58, 0xdf, 0xa5, 0x4f, 0x40, 0x83, 0x29,
	0x7c, 0x49, 0xf8, 0x57, 0x9c, 0xcc, 0xfb, 0x55, 0xa4, 0x1f, 0xc5, 0x93,
	0x84, 0x2f, 0xe0, 0x1a, 0x86, 0x6b, 0x49, 0xbf, 0x19, 0xd7, 0x13, 0xdc,
	0xc1, 0x53, 0x8c, 0x76, 0x25, 0x7d, 0xd1, 0x41, 0x2c, 0xcd, 0xe7, 0x6e,
	0x25, 0xcb, 0x67, 0x06, 0x70, 0x0a, 0xdf, 0xb2, 0xfb, 0xcf, 0x38, 0xb1,
	0xaa, 0x59, 0x8f, 0x0d, 0x38, 0x88, 0x76, 0xb7, 0x8e, 0x5d, 0x16, 0x34,
	0xaf, 0x13, 0xfe, 0x1b, 0x97, 0x31, 0xb4, 0x5a, 0x09, 0x47, 0xf0, 0x38,
	0x0d, 0x74, 0x09, 0x9b, 0xd6, 0x18, 0x34, 0xf7, 0xb1, 0x67, 0x2d, 0x67,
	0x38, 0x8e, 0x4f, 0x85, 0x7b, 0xa7, 0xfe, 0xe5, 0xde, 0x9e, 0x06, 0x0d,
	0xb6, 0xe0, 0x46, 0x61, 0xa2, 0x17, 0x18, 0x5f, 0x69, 0xb3, 0x9e, 0x07,
	0x4d, 0xb1, 0xe1, 0x08, 0x1e, 0x14, 0x13, 0xec, 0x0e, 0x76, 0x57, 0x09,
	0x9a, 0xa2, 0x88, 0xe3, 0x78, 0x93, 0x1b, 0xaf, 0x68, 0xa8, 0xbe, 0x06,
	0x0d, 0x5a, 0x38, 0xbd, 0xec, 0x95, 0x9a, 0xce, 0x0f, 0xca, 0x3a, 0x41,
	0x93, 0x43, 0x65, 0x26, 0x15, 0x80, 0x39, 0xb4, 0xab, 0x04, 0x4d, 0x71,
	0x14, 0xfb, 0x70, 0x37, 0x8f, 0xa2, 0x83, 0x7b, 0x18, 0xc3, 0xd5, 0xbe,
	0x07, 0x4d, 0x51, 0x44, 0x3b, 0xbb, 0x87, 0x5f, 0x78, 0x58, 0x35, 0x68,
	0xd2, 0x0f, 0xd3, 0xe9, 0x83, 0x25, 0xc9, 0xeb, 0x06, 0x0d, 0x86, 0x70,
	0xa5, 0x80, 0xc3, 0xcb, 0xae, 0x83, 0xa6, 0x47, 0x45, 0xec, 0xc7, 0xb3,
	0x62, 0xd6, 0x9f, 0xc1, 0x40, 0xd5, 0x7f, 0x43, 0x1c, 0x89, 0x88, 0xa3,
	0x11, 0x31, 0x17, 0x11, 0x17, 0x9b, 0xa6, 0x99, 0xaf, 0xfe, 0x27, 0x9b,
	0x89, 0xd9, 0xaa, 0x26, 0x7d, 0x8d, 0xf5, 0x07, 0xad, 0xd5, 0x8d, 0xfc,
	0x3e, 0xab, 0x6e, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
	0xae, 0x42, 0x60, 0x82
};

#pragma mark - Object

/**
 * @see Object::dealloc(Object *)
 */
static void dealloc(Object *self) {

	Checkbox *this = (Checkbox *) self;

	release(this->box);
	release(this->check);

	super(Object, self, dealloc);
}

#pragma mark - View

/**
 * @see View::awakeWithDictionary(View *, const Dictionary *)
 */
static void awakeWithDictionary(View *self, const Dictionary *dictionary) {

	super(View, self, awakeWithDictionary, dictionary);

	Checkbox *this = (Checkbox *) self;

	const Inlet inlets[] = MakeInlets(
		MakeInlet("check", InletTypeView, &this->check, NULL)
	);

	$(self, bind, inlets, dictionary);
}

/**
 * @see View::draw(View *self, Renderer *renderer)
 */
static void draw(View *self, Renderer *renderer) {

	Checkbox *this = (Checkbox *) self;

	if (this->control.state & ControlStateSelected) {
		this->check->view.hidden = false;
	} else {
		this->check->view.hidden = true;
	}

	super(View, self, draw, renderer);
}

/**
 * @see View::init(View *)
 */
static View *init(View *self) {
	return (View *) $((Checkbox *) self, initWithFrame, NULL, ControlStyleDefault);
}

#pragma mark - Control

/**
 * @see Control::captureEvent(Control *, const SDL_Event *)
 */
static _Bool captureEvent(Control *self, const SDL_Event *event) {

	if (event->type == SDL_MOUSEBUTTONUP) {

		Checkbox *this = (Checkbox *) self;

		if ($((View *) this->box, didReceiveEvent, event)) {
			self->state ^= ControlStateSelected;
			return true;
		}
	}

	return super(Control, self, captureEvent, event);
}

#pragma mark - Checkbox

/**
 * @fn Checkbox *Checkbox::initWithFrame(Checkbox *self, const SDL_Frame *frame, ControlStyle style)
 * @memberof Checkbox
 */
static Checkbox *initWithFrame(Checkbox *self, const SDL_Rect *frame, ControlStyle style) {

	self = (Checkbox *) super(Control, self, initWithFrame, frame, style);
	if (self) {

		self->control.view.autoresizingMask = ViewAutoresizingContain;

		self->box = $(alloc(Control), initWithFrame, frame, style);
		assert(self->box);

		self->box->view.alignment = ViewAlignmentMiddleCenter;

		self->check = $(alloc(ImageView), initWithImage, _check);
		assert(self->check);

		self->check->view.autoresizingMask = ViewAutoresizingFill;

		$((View *) self->box, addSubview, (View *) self->check);
		$((View *) self, addSubview, (View *) self->box);

		if (self->control.style == ControlStyleDefault) {
			self->box->bevel = ControlBevelTypeInset;

			self->box->view.backgroundColor = Colors.Charcoal;
			self->box->view.backgroundColor.a = 48;

			self->box->view.frame.w = DEFAULT_CHECKBOX_SIZE;
			self->box->view.frame.h = DEFAULT_CHECKBOX_SIZE;

			self->box->view.padding.top = DEFAULT_CHECKBOX_PADDING;
			self->box->view.padding.right = DEFAULT_CHECKBOX_PADDING;
			self->box->view.padding.bottom = DEFAULT_CHECKBOX_PADDING;
			self->box->view.padding.left = DEFAULT_CHECKBOX_PADDING;
		}
	}

	return self;
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {

	((ObjectInterface *) clazz->def->interface)->dealloc = dealloc;

	((ViewInterface *) clazz->def->interface)->draw = draw;
	((ViewInterface *) clazz->def->interface)->awakeWithDictionary = awakeWithDictionary;
	((ViewInterface *) clazz->def->interface)->init = init;

	((ControlInterface *) clazz->def->interface)->captureEvent = captureEvent;

	((CheckboxInterface *) clazz->def->interface)->initWithFrame = initWithFrame;

	_check = $(alloc(Image), initWithBytes, _checkData, lengthof(_checkData));
}

/**
 * @see Class::destroy(Class *)
 */
static void destroy(Class *clazz) {
	release(_check);
}

/**
 * @fn Class *Checkbox::_Checkbox(void)
 * @memberof Checkbox
 */
Class *_Checkbox(void) {
	static Class clazz;
	static Once once;

	do_once(&once, {
		clazz.name = "Checkbox";
		clazz.superclass = _Control();
		clazz.instanceSize = sizeof(Checkbox);
		clazz.interfaceOffset = offsetof(Checkbox, interface);
		clazz.interfaceSize = sizeof(CheckboxInterface);
		clazz.initialize = initialize;
		clazz.destroy = destroy;
	});

	return &clazz;
}

#undef _Class
