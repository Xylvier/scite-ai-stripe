// SciTE - Scintilla based Text Editor
/** @file StyleDefinition.h
 ** Definition of style aggregate and helper functions.
 **/
// Copyright 2013 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef STYLEDEFINITION_H
#define STYLEDEFINITION_H

class StyleDefinition {
public:
	std::string font;
	float sizeFractional;
	int size;
	std::string fore;
	std::string back;
	Scintilla::FontWeight weight;
	Scintilla::FontStretch stretch;
	bool italics;
	bool eolfilled;
	bool underlined;
	Scintilla::CaseVisible caseForce;
	bool visible;
	bool changeable;
	std::string invisibleRep;
	enum flags { sdNone = 0, sdFont = 0x1, sdSize = 0x2, sdFore = 0x4, sdBack = 0x8,
		     sdWeight = 0x10, sdItalics = 0x20, sdEOLFilled = 0x40, sdUnderlined = 0x80,
		     sdCaseForce = 0x100, sdVisible = 0x200, sdChangeable = 0x400, sdInvisibleRep=0x800,
		     sdStretch = 0x10000,
		   } specified;
	explicit StyleDefinition(std::string_view definition);
	bool ParseStyleDefinition(std::string_view definition);
	[[nodiscard]] Scintilla::Colour Fore() const noexcept;
	[[nodiscard]] Scintilla::Colour Back() const noexcept;
	[[nodiscard]] int FractionalSize() const noexcept;
	[[nodiscard]] bool IsBold() const noexcept;
};

static constexpr int shiftGreen = 8;
static constexpr int shiftBlue = 16;
static constexpr int shiftAlpha = 24;
static constexpr unsigned int alphaOpaque = 0xff;

constexpr Scintilla::Colour ColourRGB(unsigned int red, unsigned int green, unsigned int blue) noexcept {
	return red | (green << shiftGreen) | (blue << shiftBlue);
}

constexpr Scintilla::ColourAlpha ColourRGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha=alphaOpaque) noexcept {
	return red | (green << shiftGreen) | (blue << shiftBlue) | (alpha << shiftAlpha);
}

Scintilla::Colour ColourFromString(std::string_view s) noexcept;
Scintilla::ColourAlpha ColourAlphaFromString(std::string_view s) noexcept;

struct IndicatorDefinition {
	Scintilla::IndicatorStyle style;
	Scintilla::Colour colour;
	Scintilla::Alpha fillAlpha;
	Scintilla::Alpha outlineAlpha;
	bool under;
	explicit IndicatorDefinition(std::string_view definition);
	bool ParseIndicatorDefinition(std::string_view definition);
};

struct MarkerDefinition {
	Scintilla::MarkerSymbol style;
	Scintilla::Colour colour;
	Scintilla::Colour back = ColourRGB(0xFF,0xFF,0xFF);
	explicit MarkerDefinition(std::string_view definition);
	bool ParseMarkerDefinition(std::string_view definition);
};

#endif
