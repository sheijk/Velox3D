/*
 * Created on 14.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Iterator;
import java.util.LinkedList;

import de.janrehders.gse2.accounts.*;
import de.janrehders.gse2.controller.Controller;
import de.janrehders.gse2.model.Model;
import de.janrehders.gse2.view.MainWindow;

/**
 * Tests the ui with null functionality
 * 
 * @author Jan Rehders
 */
public class TestView {
    public static void main(String[] args) {
        Model model = new EchoModel();
        Controller controller = new Controller(model);
        MainWindow mainWindow = new MainWindow(controller);
    }

    /**
     * A simple static model. Does not execute any changes but prints them
     * to the console for test purposes. Contains some test accounts to test
     * the different windows
     * 
     * @author Jan Rehders
     */
    public static class EchoModel implements Model {
        private LinkedList myAccounts = new LinkedList();
        
        public EchoModel()
        {
            // add giro
            myAccounts.add(new Giro());
            
            // add student giro
            myAccounts.add(new StudentGiro());
            
            // add savings
            myAccounts.add(new Savings());
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#addAccount(de.janrehders.gse2.accounts.Account)
         */
        public boolean insert(Account inAccount) {
            System.out.println("created new account: ");
            inAccount.show();
            
            return true;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#removeAccount(de.janrehders.gse2.accounts.Account)
         */
        public boolean remove(Account inAccount) {
            System.out.println("removed account:");
            inAccount.show();
            
            return false;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#updateAccount(int, de.janrehders.gse2.accounts.Account)
         */
        public boolean update(int inAccountId, Account inAccount) {
            System.out.println("updated account with id " + inAccountId + ":");
            inAccount.show();
            
            return true;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#accountIterator()
         */
        public AccountIterator accountIterator() {
            final Iterator iter = myAccounts.iterator();
            
            return new AccountIterator() {
                public Account next() { 
                    return (Account) iter.next(); 
                }
                
                public boolean hasNext()
                { 
                    return iter.hasNext();
                }
            };
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#getById(int)
         */
        public Account getById(int inAccountId) {
            AccountIterator iter = accountIterator();
            while(iter.hasNext())
            {
                Account account = iter.next();
                
                if( account.getAccountNo() == inAccountId )
                    return account;
            }
            
            return null;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#writeToStream(java.io.OutputStream)
         */
        public boolean writeToStream(OutputStream out_ioStream) {
            System.out.println("Attempted to save model to stream");
            return true;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#loadFromStream(java.io.InputStream)
         */
        public boolean loadFromStream(InputStream out_ioStream) {
            System.out.println("Attempted to load model from stream");
            return true;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#erase()
         */
        public void scratch() {
            System.out.println("Erased model");
        }
    }
}
