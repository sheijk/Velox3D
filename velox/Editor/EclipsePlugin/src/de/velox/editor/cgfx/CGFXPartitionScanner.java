package de.velox.editor.cgfx;

import java.util.LinkedList;

import org.eclipse.jface.text.rules.*;

public class CGFXPartitionScanner extends RuleBasedPartitionScanner {
	public final static String CGFX_DEFAULT = "__cgfx_default";
	public final static String CGFX_COMMENT = "__cgfx_comment";
//	public final static String CGFX_KEYWORD = "__cgfx_keyword";

	public CGFXPartitionScanner() {

		IToken comment = new Token(CGFX_COMMENT);
//		IToken keyword = new Token(CGFX_KEYWORD);

		LinkedList<IPredicateRule> predRules = new LinkedList<IPredicateRule>();
//		LinkedList<IRule> rules = new LinkedList<IRule>();

		predRules.add( new MultiLineRule("/*", "*/", comment) );
		predRules.add( new EndOfLineRule("//", comment));

//		WordRule wr = new WordRule(new KeywordDetector(), comment);
//		wr.addWord("float4", keyword);
//		wr.addWord("technique", keyword);
//		wr.addWord("pass", keyword);
//		rules.add(wr);

		setPredicateRules(predRules.toArray(new IPredicateRule[0]));
//		setRules(rules.toArray(new IRule[0]));
	}
	
//	private static final class KeywordDetector implements IWordDetector {
//		public boolean isWordStart(char c) {
//			return isWordPart(c);
//		}
//
//		public boolean isWordPart(char c) {
//			return Character.toString(c).matches("[a-z][0-9]"); 
//		}
//	}
}
