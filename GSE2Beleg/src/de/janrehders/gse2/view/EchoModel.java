/*
 * Created on 06.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Iterator;
import java.util.LinkedList;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountIterator;
import de.janrehders.gse2.model.Model;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class EchoModel implements Model {
    private LinkedList myAccounts = new LinkedList();

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#addAccount(de.janrehders.gse2.accounts.Account)
     */
    public boolean addAccount(Account inAccount) {
        System.out.println("created new account: ");
        inAccount.show();
        
        return myAccounts.add(inAccount);
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#removeAccount(de.janrehders.gse2.accounts.Account)
     */
    public boolean removeAccount(Account inAccount) {
        System.out.println("removed account:");
        inAccount.show();
        
        return myAccounts.remove(inAccount);
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#updateAccount(int, de.janrehders.gse2.accounts.Account)
     */
    public boolean updateAccount(int inAccountId, Account inAccount) {
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
    public void erase() {
        System.out.println("Erased model");
    }

}
