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
public class OrderedRegisterTests extends TestCase {
    /** vorgegebener TestCase 1 */
    public void testCopy()
    {
        OrderedRegister reg1 = new OrderedRegister();
        OrderedRegister reg2 = new OrderedRegister();
        assertTrue(reg2.classInvariant());
        
        assertTrue(reg1.copy(reg2));
        assertTrue(reg1.classInvariant());
        assertTrue(reg1.equals(reg2));
    }
    
    /**
     * vorgegebener TestCase 2
     * 
     * abgeaendert, wegen Interatoren statt GetActual
     */
    public void testInsertFind()
    {
        OrderedRegister reg = new OrderedRegister();
        TestAccount acc1 = new TestAccount();
        assertTrue(reg.classInvariant());
        assertTrue(acc1.classInvariant());
        
        assertTrue(reg.insert(acc1));
        assertTrue(reg.find(acc1));
    }

    /** vorgegebener TestCase 3 */
    public void testScratch()
    {
        OrderedRegister reg = new OrderedRegister();
        TestAccount acc1 = new TestAccount();
        assertTrue(reg.insert(acc1));
        assertTrue(reg.classInvariant());
        assertTrue(acc1.classInvariant());
        
        assertTrue(reg.find(acc1));
        assertTrue(reg.scratch());
        assertFalse(reg.find(acc1));
    }
    
    /** vorgegebener TestCase 4 */
    public void testCard()
    {
        OrderedRegister reg = new OrderedRegister();
        Account acc = new TestAccount();
        final int n1 = reg.card();
        assertTrue(reg.classInvariant());
        assertFalse(reg.find(acc));
        assertTrue(acc.classInvariant());
        
        assertTrue(reg.insert(acc));
        assertEquals(n1+1, reg.card());
    }
    
    /** 
     * vorgegebener TestCase 5
     * abgewandelt wegen iteratoren statt cursor, remove statt scratch
     */
    public void testScratchFindCard()
    {
        OrderedRegister reg = new OrderedRegister();
        TestAccount acc = new TestAccount();
        assertTrue(reg.insert(acc));
        final int n1 = reg.card();
        
        assertTrue(reg.remove(acc));
        assertEquals(n1-1, reg.card());
    }

}
