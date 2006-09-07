/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.cgfx;

import java.util.LinkedList;

import org.eclipse.jface.text.rules.*;
import org.eclipse.jface.text.*;
import org.eclipse.swt.graphics.RGB;

public class CGFXScanner extends RuleBasedScanner {

	private final static String[] KEYWORDS = {
		"technique", "pass",
		"true", "false",
		"void", "string",
		"return", "if", "else", "while", "for", "continue",
		"struct",
		
		"float", "float1", "float2", "float3", "float4",
		"half", "half1", "half2", "half3", "half4",
		"fixed", "fixed1", "fixed2", "fixed3", "fixed4",
		"int", "int1", "int2", "int3", "int4",
		"bool", "bool1", "bool2", "bool3", "bool4",
		
		"sampler1D", "sampler2D", "sampler3D", "samplerCUBE", "samplerRECT",
		
		"uniform", "packed", "typedef", "const", "in", "out", "inout",
		"discard",
		"compile",
		
		"POSITION", "PSIZE",
		"COLOR", "COLOR0", "DEPTH",
		"arbvp1", "arbfp1",
		"vp20", "fp20", "vp30", "fp30", "vp40", "fp40"
	};
	
	private final static String[] STDLIB_NAMES = {		
		"abs", "acos", "all", "any", "asin", "atan", "atan2", 
		"ceil", "clamp", "cos", "cosh", "cross",
		"degrees", "determinant", "dot", "ddx", "ddy", "debug", "distance",
		"exp", "exp2",
		"floor", "fmod", "frac", "frexp", "fragout", "fragout_float", "faceforward",
		"isinfinite", "isinf", "isnan",
		"ldexp", "lerp", "lit", "log", "log2", "log10", "length",
		"max", "min", "modf", "mul",
		"noise", "normalize",
		"pow",
		"radians", "round", "rsqrt", "reflect", "refract",
		"saturate", "sign", "sin", "sincos", "sinh", "smoothstep", "step", "sqrt",
		"tan", "tanh", "transpose",

		"tex1D", "tex1Dproj", 
		"tex2D", "tex2Dproj", 
		"texRECT", "texRECTproj",
		"tex3D", "tex3Dproj",
		"texCUBE", "texCUBEproj",
	};
	
	private final static String[] STATE_NAMES = {
		"FragmentProgram", "VertexProgram",
		"Zenable"
	};
	
	private final static String[] RESERVED_WORDS = {
		"switch", "case", "default"
	};
	
	private final ColorManager myColorManager;
	
	public CGFXScanner(ColorManager manager) {
		myColorManager = manager;
		
		final IToken defaultToken = coloredToken(ColorConstants.DEFAULT);		
		final IToken keywordToken = coloredToken(ColorConstants.CGFX_KEYWORD);
		final IToken stateToken = coloredToken(ColorConstants.CGFX_STATE);
		final IToken stringToken = coloredToken(ColorConstants.CGFX_STRING);
		final IToken reservedToken = coloredToken(ColorConstants.CGFX_RESERVED);

		LinkedList<IRule> rules = new LinkedList<IRule>();

		rules.add( new SingleLineRule("\"", "\"", stringToken, '\\') );
		
		WordRule wr = new WordRule(new KeywordDetector(), defaultToken);
		for(String keyword : KEYWORDS) {
			wr.addWord(keyword, keywordToken);
		}
		
		// generate matrix type names (float4x4 etc)
		final String[] basicTypes = { "float", "half", "int", "bool", "fixed" };
		for(String t : basicTypes)
		for(int r = 1; r <= 4; ++r)
		for(int c = 1; c <= 4; ++c) {
			String matName = t + r + "x" + c;
			wr.addWord(matName, keywordToken);
		}
		
		for(String stateName : STDLIB_NAMES) {
			wr.addWord(stateName, stateToken);
		}
		
		for(String reservedWord : RESERVED_WORDS) {
			wr.addWord(reservedWord, reservedToken);
		}
		
		for(String stateName : STATE_NAMES) {
			wr.addWord(stateName, stateToken);
		}
		rules.add( wr );
		
		rules.add( new WhitespaceRule(new WhitespaceDetector()) );

		setRules(rules.toArray(new IRule[0]));
	}
	
	private IToken coloredToken(RGB color) {
		return new Token(new TextAttribute(myColorManager.getColor(color)));
	}
	
	private static final class KeywordDetector implements IWordDetector {
		public boolean isWordStart(char c) {
			return isWordPart(c);
		}
	
		public boolean isWordPart(char c) {
			return Character.toString(c).matches("[a-zA-Z0-9]");
		}
	}
}

