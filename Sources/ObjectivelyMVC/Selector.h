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

#pragma once

#include <Objectively/Array.h>
#include <Objectively/String.h>

#include <ObjectivelyMVC/SelectorSequence.h>

/**
 * @file
 * @brief The Selector type.
 */

typedef struct Selector Selector;
typedef struct SelectorInterface SelectorInterface;

/**
 * @brief Selectors are comprised of one or more SelectorSequences.
 * @extends Object
 * @ingroup Theme
 */
struct Selector {

	/**
	 * @brief The superclass.
	 */
	Object object;

	/**
	 * @brief The interface.
	 * @protected
	 */
	SelectorInterface *interface;

	/**
	 * @brief The sequences.
	 */
	Array *sequences;

	/**
	 * @brief The rule, as provided by the user.
	 */
	char *rule;

	/**
	 * @brief The specificity.
	 */
	int specificity;
};

/**
 * @brief The Selector interface.
 */
struct SelectorInterface {

	/**
	 * @brief The superclass interface.
	 */
	ObjectInterface objectInterface;

	/**
	 * @fn Order Selector::compareTo(const Selector *self, const Selector *other)
	 * @brief Compares this Selector to `other`, ordering by specificity.
	 * @param self The Selector.
	 * @param other The Selector to compare.
	 * @return The comparison result.
	 * @memberof Selector
	 */
	Order (*compareTo)(const Selector *self, const Selector *other);

	/**
	 * @fn Selector *Selector::initWithRule(Selector *self, const char *rule)
	 * @brief Initializes this Selector with the given rule.
	 * @param self The Selector.
	 * @param rule The rule.
	 * @return The initialized Selector, or `NULL` on error.
	 * @memberof Selector
	 */
	Selector *(*initWithRule)(Selector *self, const char *rule);

	/**
	 * @static
	 * @fn Array *Selector::parse(const char *rules)
	 * @brief Parses the null-terminated C string of Selector rules into an Array of Selectors.
	 * @param chars A null-terminated C string of Selector rules.
	 * @return An Array of Selectors.
	 * @memberof Selector
	 */
	Array *(*parse)(const char *rules);

	/**
	 * @fn _Bool Selector::matches(const Selector *selector, const View *view)
	 * @param self The Selector.
	 * @param view The View.
	 * @return True if this Selector matches `view`, false otherwise.
	 * @memberof Selector
	 */
	_Bool (*matches)(const Selector *self, const View *view);
};

/**
 * @fn Class *Selector::_Selector(void)
 * @brief The Selector archetype.
 * @return The Selector Class.
 * @memberof Selector
 */
OBJECTIVELY_EXPORT Class *_Selector(void);