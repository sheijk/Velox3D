/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/*
 * Created on Jul 16, 2005
 */
package de.velox.editor.temp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegExTest {

//	public static void main(String[] args) {
//		String childSource = 
//			"<entity name=\"lala\">\n" +
//			"<part prop=\"abc\">\n" +
//			"	<internal blub=\"xyz\" />\n" +
//			"</part>\n" +
//			"</entity>\n";
//		
//		Matcher m = Pattern.compile(".*\n").matcher(childSource);
//		String indentedChildSource = m.replaceAll("\t$0");
//		
//		System.out.println("Original source\n\n" + childSource);
//		System.out.println("\n\nReplaced with\n\n" + indentedChildSource);
//	}

	private static String generateDisplayName(final String fileName) {
		Pattern pattern = Pattern.compile(".*[\\/\\\\]([^\\.]+)\\..*");
		Matcher matcher = pattern.matcher(fileName);

		if( matcher.find() )
			return matcher.group(1);
		else
			return fileName;
	}
	
	public static void main(String[] args) {
		String[] testCases = {
				"g:/foo/bar/some/more/file.v3dmat", "file",
				"~/Documents/foo/bar/file.v3dmat", "file",
				"c:\\windows\\is\\the\\wurst\\case.v3dscene", "case"
		};

		for(int i = 0; i < testCases.length; i += 2) {
			final String test = testCases[i];
			final String expected = testCases[i+1];
			
			System.out.println("trying " + test);
			
			final String result = generateDisplayName(test);
			
			if( ! expected.equals(result) ) {
				System.err.println("expected: " + expected + " but got: " + result);
			}
		}
	}
}

