/*
 * Created on Jul 16, 2005
 */
package de.velox.editor.temp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegExTest {

	public static void main(String[] args) {
		String childSource = 
			"<entity name=\"lala\">\n" +
			"<part prop=\"abc\">\n" +
			"	<internal blub=\"xyz\" />\n" +
			"</part>\n" +
			"</entity>\n";
		
		Matcher m = Pattern.compile(".*\n").matcher(childSource);
		String indentedChildSource = m.replaceAll("\t$0");
		
		System.out.println("Original source\n\n" + childSource);
		System.out.println("\n\nReplaced with\n\n" + indentedChildSource);
	}
}
