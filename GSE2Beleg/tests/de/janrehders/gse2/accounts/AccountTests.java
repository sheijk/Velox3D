/*
 * Created on 13.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import junit.framework.TestCase;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class AccountTests extends TestCase {
    /** vorgegebenener Testcase 1 */
    public void testCopy() {
        TestAccount acc2 = new TestAccount();
        TestAccount acc1 = new TestAccount();
        assertTrue(acc2.classInvariant());
        
        assertTrue(acc1.copy(acc2));
        assertTrue(acc1.classInvariant());
        assertTrue(acc1.equals(acc2));        
    }

    /** vorgegebenener Testcase 2 */
    public void testDeposit() {
        TestAccount acc2 = new TestAccount();
        TestAccount acc1 = new TestAccount();
        assertTrue(acc2.classInvariant());
        
        assertTrue(acc1.copy(acc2));
        assertTrue(acc1.deposit(100));
        assertFalse(acc1.equals(acc2));
    }

	/* Vorbedingungen:	Account acc1. acc1.getBalance() = startBalance
	 * Nachbedingungen:	acc1.getBalance() = startBalance + depositAmount
	 * 					- withdrawAmount;
	 */
	public void testDepositWithdraw() {
		final float startBalance = 100.0f;
		final float depositAmount = 30.0f;
		final float withdrawAmount = 64.0f;
		
		Account acc1 = new TestAccount(
				2, new AccountType(1), "owner", startBalance);
		
		assertTrue(acc1.deposit(depositAmount));
		assertTrue(acc1.withDraw(withdrawAmount));
		assertTrue(
				acc1.getBalance() == 
				startBalance + depositAmount - withdrawAmount
				);
	}
}
