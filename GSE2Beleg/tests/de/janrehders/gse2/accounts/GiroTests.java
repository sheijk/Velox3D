/*
 * Created on 02.04.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import junit.framework.TestCase;
import java.util.Date;

/**
 * Testfaelle fuer Giro
 * 
 * @author Jan Rehders 
 */
public class GiroTests extends TestCase {
    /** vorgegebener TestCase 1 */
	public void testCopyEqual() {
	    Giro gir2 = new Giro();
	    Giro gir1 = new Giro();
	    assertTrue(gir2.classInvariant());
	    
	    assertTrue(gir1.copy(gir2));
	    assertTrue(gir1.classInvariant());
	    assertTrue(gir1.equals(gir2));
	}

	/** vorgegebener TestCase 2 */
	public void testTransfer() {
	    Giro gir2 = new Giro();
	    Giro gir1 = new Giro();
	    assertTrue(gir2.classInvariant());
	    
	    assertTrue(gir2.deposit(100));
	    assertTrue(gir1.copy(gir2));
	    assertTrue(gir1.transfer(gir2, 100));
	    assertFalse(gir1.equals(gir2));
	}
	
	/* Vorbedingung:	Giro giro mit 50.0 Betrag, Dispo Line 100.0f
	 * Nachbedingung:	giro.withDraw(150) == true
	 */
	public void testCreditLimit() {
		Giro giro = new Giro(1, new AccountType(1), "tester", 50.0f, 100.0f, 2, new Date());
		
		assertTrue(giro.withDraw(150.0f));
		assertFalse(giro.withDraw(1));
	}
	
	/* Vorbedingung:	Giro giro mit 50.0 Betrag und 100.0 Disp Credit Line
	 * Nachbedingung:	giro.withDraw(151) == false, giro.getBalance() == 50.0
	 */
	public void testCreditLimit2() {
		Giro giro = new Giro(1, new AccountType(1), "tester", 50.0f, 100.0f, 2, new Date());
		
		assertFalse(giro.withDraw(151.0f));
		assertTrue(giro.getBalance() == 50.0f);
	}
}
