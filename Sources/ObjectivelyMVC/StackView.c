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

#include <ObjectivelyMVC/StackView.h>

static const EnumName StackViewAxisNames[] = {
	NameEnum(StackViewAxisVertical),
	NameEnum(StackViewAxisHorizontal),
	EnumNameLast
};

static const EnumName StackViewDistributionNames[] = {
	NameEnum(StackViewDistributionDefault),
	NameEnum(StackViewDistributionFill),
	NameEnum(StackViewDistributionFillEqually),
	EnumNameLast
};

#define _Class _StackView

#pragma mark - View

/**
 * @see View::awakeWithDictionary(View *, const Dictionary *)
 */
static void awakeWithDictionary(View *self, const Dictionary *dictionary) {

	super(View, self, awakeWithDictionary, dictionary);

	StackView *this = (StackView *) self;

	const Inlet *inlets = MakeInlets(
		MakeInlet("axis", InletTypeEnum, &this->axis, (ident) StackViewAxisNames),
		MakeInlet("distribution", InletTypeEnum, &this->distribution, (ident) StackViewDistributionNames),
		MakeInlet("spacing", InletTypeInteger, &this->spacing, NULL)
	);

	$(self, bind, dictionary, inlets);
}

/**
 * @see View::init(View *)
 */
static View *init(View *self) {
	return (View *) $((StackView *) self, initWithFrame, NULL);
}

/**
 * @see View::layoutSubviews(View *)
 */
static void layoutSubviews(View *self) {

	super(View, self, layoutSubviews);

	Array *subviews = $(self, visibleSubviews);
	if (subviews->count) {

		StackView *this = (StackView *) self;

		const SDL_Rect bounds = $(self, bounds);

		int availableSize, requestedSize = 0;
		switch (this->axis) {
			case StackViewAxisVertical:
				availableSize = bounds.h;
				break;
			case StackViewAxisHorizontal:
				availableSize = bounds.w;
				break;
		}

		availableSize -= this->spacing * (subviews->count - 1);

		for (size_t i = 0; i < subviews->count; i++) {

			const View *subview = $(subviews, objectAtIndex, i);
			const SDL_Size size = $(subview, sizeThatFits);

			switch (this->axis) {
				case StackViewAxisVertical:
					requestedSize += size.h;
					break;
				case StackViewAxisHorizontal:
					requestedSize += size.w;
					break;
			}
		}

		int pos;
		switch (this->axis) {
			case StackViewAxisVertical:
				pos = bounds.y;
				break;
			case StackViewAxisHorizontal:
				pos = bounds.x;
				break;
		}

		const float scale = requestedSize ? availableSize / (float) requestedSize : 1.0;

		for (size_t i = 0; i < subviews->count; i++) {

			View *subview = $(subviews, objectAtIndex, i);

			switch (this->axis) {
				case StackViewAxisVertical:
					subview->frame.y = pos;
					break;
				case StackViewAxisHorizontal:
					subview->frame.x = pos;
					break;
			}

			const SDL_Size before = $(subview, size);

			switch (this->distribution) {
				case StackViewDistributionDefault:
					break;

				case StackViewDistributionFill:
					switch (this->axis) {
						case StackViewAxisVertical:
							subview->frame.h *= scale;
							break;
						case StackViewAxisHorizontal:
							subview->frame.w *= scale;
							break;
					}
					break;

				case StackViewDistributionFillEqually:
					switch (this->axis) {
						case StackViewAxisVertical:
							subview->frame.h = availableSize / (float) subviews->count;
							break;
						case StackViewAxisHorizontal:
							subview->frame.w = availableSize / (float) subviews->count;
							break;
					}
					break;
			}

			const SDL_Size after = $(subview, size);

			if (before.w != after.w || before.h != after.h) {
				$(subview, layoutSubviews);
			}

			switch (this->axis) {
				case StackViewAxisVertical:
					pos += subview->frame.h;
					break;
				case StackViewAxisHorizontal:
					pos += subview->frame.w;
					break;
			}
			
			pos += this->spacing;
		}
	}
	
	release(subviews);
}

/**
 * @see View::sizeThatFits(const View *)
 */
static SDL_Size sizeThatFits(const View *self) {
	
	const StackView *this = (StackView *) self;
	
	SDL_Size size = MakeSize(0, 0);
	
	Array *subviews = $(self, visibleSubviews);
	if (subviews->count) {
		
		for (size_t i = 0; i < subviews->count; i++) {
			
			const View *subview = $(subviews, objectAtIndex, i);

			switch (this->axis) {
				case StackViewAxisVertical:
					size.w = max(size.w, subview->frame.w);
					size.h += subview->frame.h;
					break;
				case StackViewAxisHorizontal:
					size.h = max(size.h, subview->frame.h);
					size.w += subview->frame.w;
					break;
			}
		}
		
		switch (this->axis) {
			case StackViewAxisVertical:
				size.h += this->spacing * (subviews->count - 1);
				break;
			case StackViewAxisHorizontal:
				size.w += this->spacing * (subviews->count - 1);
				break;
		}
	}

	size.w += self->padding.left + self->padding.right;
	size.h += self->padding.top + self->padding.bottom;

	release(subviews);

	return size;
}

#pragma mark - StackView

/**
 * @fn StackView *StackView::initWithFrame(StackView *self, const SDL_Rect *frame)
 *
 * @memberof StackView
 */
static StackView *initWithFrame(StackView *self, const SDL_Rect *frame) {

	self = (StackView *) super(View, self, initWithFrame, frame);
	if (self) {
		self->view.autoresizingMask = ViewAutoresizingContain;
	}

	return self;
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {

	((ViewInterface *) clazz->interface)->awakeWithDictionary = awakeWithDictionary;
	((ViewInterface *) clazz->interface)->init = init;

	((ViewInterface *) clazz->interface)->layoutSubviews = layoutSubviews;
	((ViewInterface *) clazz->interface)->sizeThatFits = sizeThatFits;
	
	((StackViewInterface *) clazz->interface)->initWithFrame = initWithFrame;
}

Class _StackView = {
	.name = "StackView",
	.superclass = &_View,
	.instanceSize = sizeof(StackView),
	.interfaceOffset = offsetof(StackView, interface),
	.interfaceSize = sizeof(StackViewInterface),
	.initialize = initialize,
};

#undef _Class
