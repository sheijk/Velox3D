/*
 * Created on 14.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.controller;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Observable;
import java.util.Observer;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountIterator;
import de.janrehders.gse2.accounts.TestAccount;
import de.janrehders.gse2.model.Model;
import junit.framework.TestCase;

/**
 * Tests for the Controller
 * 
 * @author Jan Rehders
 */
public class ControllerTests extends TestCase {
    /** 
     * Tests whether notifying on changes works
     *
     * Precondition: controller is of type Controller
     * 
     * Ensure: observer.notify has been called  
     */
   public void testNotify()
   {
       Controller controller = new Controller(new DummyModel());
       TestObserver testObserver = new TestObserver();
       controller.addObserver(testObserver);
       
       controller.getModel().update(0, new TestAccount());
       assertTrue(testObserver.hasBeenNotified());
   }

   /** Simple Observer tests class. Stores whether it has been notified */
   private static class TestObserver implements Observer
   {
       private boolean myHasBeenNotified = false;
       
       /** returns whether update has been called */
       public boolean hasBeenNotified() { return myHasBeenNotified; }
       
       /* (non-Javadoc)
        * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
        */
       public void update(Observable out_o, Object out_arg) {
           myHasBeenNotified = true;
       }
   }
   
   /** A dummy model. Used for testing purposes as a non functional dummy. */
   private static class DummyModel implements Model
   {
       public boolean insert(Account inAccount) { return true; }
       public boolean remove(Account inAccount) { return true; }
       public boolean update(int inAccountId, Account inAccount) { return true; }
       public AccountIterator accountIterator() { return null; }
       public Account getById(int inAccountId) { return null; }
       public void scratch() {}
       public boolean writeToStream(OutputStream out_ioStream) { return true; }
       public boolean loadFromStream(InputStream out_ioStream) { return true; }
   }
}
