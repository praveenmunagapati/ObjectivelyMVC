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

#include <ObjectivelyMVC/Log.h>
#include <ObjectivelyMVC/WindowController.h>

#define _Class _WindowController

#pragma mark - Object

/**
 * @see Object::dealloc(Object *)
 */
static void dealloc(Object *self) {

	WindowController *this = (WindowController *) self;

	release(this->renderer);
	release(this->responderChain);
	release(this->viewController);

	super(Object, self, dealloc);
}

#pragma mark - WindowController

/**
 * @fn View *WindowController::firstResponder(const WindowController *self, const SDL_Event *event)
 * @memberof WindowController
 */
static View *firstResponder(const WindowController *self, const SDL_Event *event) {

	View *firstResponder = MVC_FirstResponder(self->window);
	if (firstResponder == NULL) {

		const Array *responderChain = (Array *) self->responderChain;
		for (size_t i = 0; i < responderChain->count; i++) {
			View *view = $(responderChain, objectAtIndex, responderChain->count - i - 1);
			if ($(view, didReceiveEvent, event)) {
				firstResponder = view;
				break;
			}
		}
	}

	return firstResponder;
}

/**
 * @fn WindowController *WindowController::initWithWindow(WindowController *self, SDL_Window *window)
 * @memberof WindowController
 */
static WindowController *initWithWindow(WindowController *self, SDL_Window *window) {

	self = (WindowController *) super(Object, self, init);
	if (self) {

		self->window = window;
		assert(self->window);

		const Uint32 flags = SDL_GetWindowFlags(self->window);
		assert(flags & SDL_WINDOW_OPENGL);

		self->renderer = $(alloc(Renderer), init);
		assert(self->renderer);

		self->responderChain = $$(MutableArray, array);
		assert(self->responderChain);
	}

	return self;
}

/**
 * @fn void WindowController::render(WindowController *self)
 * @memberof WindowController
 */
static void render(WindowController *self) {

	assert(self->renderer);

	$(self->renderer, beginFrame);

	$(self->responderChain, removeAllObjects);

	if (self->viewController) {
		Array *views = $(self->viewController, drawView);

		for (size_t i = 0; i < views->count; i++) {
			View *view = $(views, objectAtIndex, i);

			$(self->renderer, drawView, view);
			$(self->responderChain, addObject, view);
		}

		release(views);
	} else {
		MVC_LogWarn("viewController is NULL\n");
	}

	$(self->renderer, endFrame);
}

/**
 * @fn void WindowController:respondToEvent(WindowController *self, const SDL_Event *event)
 * @memberof WindowController
 */
static void respondToEvent(WindowController *self, const SDL_Event *event) {

	if (event->type == SDL_WINDOWEVENT) {
		if (event->window.event == SDL_WINDOWEVENT_SHOWN) {

			if (self->renderer) {
				$(self->renderer, renderDeviceDidReset);
			}

			if (self->viewController) {
				$(self->viewController, renderDeviceDidReset);
			}
		}
	}

	View *firstResponder = $(self, firstResponder, event);
	if (firstResponder) {
		$(firstResponder, respondToEvent, event);
	} else if (self->viewController) {
		$(self->viewController, respondToEvent, event);
	} else {
		MVC_LogDebug("firstResponder for %d is NULL\n", event->type);
	}
}

/**
 * @fn void WindowController::setRenderer(WindowController *self, Renderer *renderer)
 * @memberof WindowController
 */
static void setRenderer(WindowController *self, Renderer *renderer) {

	if (self->renderer != renderer) {

		release(self->renderer);

		if (renderer) {
			self->renderer = retain(renderer);
		} else {
			self->renderer = NULL;
		}
	}
}

/**
 * @fn void WindowController::setViewController(WindowController *self, ViewController *viewController)
 * @memberof WindowController
 */
static void setViewController(WindowController *self, ViewController *viewController) {

	if (self->viewController != viewController) {

		if (self->viewController) {
			$(self->viewController, viewWillDisappear);
			$(self->viewController->view, setWindow, NULL);
			$(self->viewController, viewDidDisappear);
		}

		release(self->viewController);

		if (viewController) {
			self->viewController = retain(viewController);
		} else {
			self->viewController = NULL;
		}

		if (self->viewController) {
			$(self->viewController, loadViewIfNeeded);

			$(self->viewController, viewWillAppear);
			$(self->viewController->view, setWindow, self->window);
			$(self->viewController, viewDidAppear);
		}
	}
}

#pragma mark - Class lifecycle

/**
 * @see Class::initialize(Class *)
 */
static void initialize(Class *clazz) {

	((ObjectInterface *) clazz->def->interface)->dealloc = dealloc;

	((WindowControllerInterface *) clazz->def->interface)->firstResponder = firstResponder;
	((WindowControllerInterface *) clazz->def->interface)->initWithWindow = initWithWindow;
	((WindowControllerInterface *) clazz->def->interface)->render = render;
	((WindowControllerInterface *) clazz->def->interface)->respondToEvent = respondToEvent;
	((WindowControllerInterface *) clazz->def->interface)->setRenderer = setRenderer;
	((WindowControllerInterface *) clazz->def->interface)->setViewController = setViewController;
}

/**
 * @fn Class *WindowController::_WindowController(void)
 * @memberof WindowController
 */
Class *_WindowController(void) {
	static Class clazz;
	static Once once;

	do_once(&once, {
		clazz.name = "WindowController";
		clazz.superclass = _Object();
		clazz.instanceSize = sizeof(WindowController);
		clazz.interfaceOffset = offsetof(WindowController, interface);
		clazz.interfaceSize = sizeof(WindowControllerInterface);
		clazz.initialize = initialize;
	});

	return &clazz;
}

#undef _Class
