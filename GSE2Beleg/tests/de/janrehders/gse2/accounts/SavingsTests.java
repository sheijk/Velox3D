/*
 * Created on 02.04.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.util.Date;

import junit.framework.TestCase;

/**
 * Testfaelle fuer Savings
 * 
 * @author Jan Rehders
 */
public class SavingsTests extends TestCase {
	/** vorgegebener test case 1 */
	public void testCloneEqual() {
	    Savings sav1 = new Savings();
	    Savings sav2 = new Savings();
	    assertTrue(sav2.classInvariant());
	    
	    assertTrue(sav1.copy(sav2));
	    assertTrue(sav1.classInvariant());
	    assertTrue(sav1.equals(sav2));
	}

	/** vorgegebener test case 2 */
	public void testDeposit() {
	    Savings sav1 = new Savings();
	    Savings sav2 = new Savings();
	    assertTrue(sav2.classInvariant());

	    assertTrue(sav1.copy(sav2));
	    assertTrue(sav1.deposit(100));
	    assertFalse(sav1.equals(sav2));
	}

	/* Vorbedingungen:	Savings sav1, sav2
	 * Nachbedingungen:	sav2.equalValue(acc1)
	 */	
	public void testCloneCopyCtor() {
		Savings sav1 = new Savings();
		Savings sav2 = new Savings(sav1);
		
		assertTrue(sav1.equals(sav2));
	}
}
