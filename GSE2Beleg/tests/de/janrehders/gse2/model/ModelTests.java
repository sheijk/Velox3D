/*
 * Created on 14.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.model;

import de.janrehders.gse2.accounts.TestAccount;
import junit.framework.TestCase;

/**
 * Testet das Model
 * 
 * @author Jan Rehders
 */
public class ModelTests extends TestCase {
    
    /**
     * Preconditions: 
     * 		model is of type ModelImpl, 
     * 		acc is of type TestAccount, acc.classInvariant holds true
     * 		id is acc.getAccountNo()
     * 
     * Sequence: 
     * 		t1 = model.insert(acc)
     * 		t2 = model.getById(id) == acc
     * 		t3 = model.remove(acc)
     * 		t4 = model.getById(id) == null
     * 
     * Ensure:
     * 		t1 - t4 = true
     */
    public void testInsertRemove()
    {
        Model model = new ModelImpl();
        TestAccount acc = new TestAccount();
        final int id = acc.getAccountNo();
        assertTrue(acc.classInvariant());
        
        assertTrue(model.insert(acc));
        assertTrue(model.getById(id) == acc);
        assertTrue(model.remove(acc));
        assertTrue(model.getById(id) == null);
    }
}
