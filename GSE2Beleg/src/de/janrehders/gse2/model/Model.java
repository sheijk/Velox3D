/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.model;

import java.io.InputStream;
import java.io.OutputStream;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountIterator;

/**
 * Interface fuer die Fachschicht
 * 
 * @author Jan Rehders
 */
public interface Model {
    /** adds an account */
    boolean addAccount(Account inAccount);
    
    /** removes an account */
    boolean removeAccount(Account inAccount);
    
    /** updates an account with new data */
    boolean updateAccount(int inAccountId, Account inAccount);
    
    /** get an iterator to access all existing acounts */
    AccountIterator accountIterator();
    
    /** get an account by it's id */
    Account getById(int inAccountId);
    
    /** remove all data */
    void erase();
    
    /** store the whole register including all accounts to a stream */
    boolean writeToStream(OutputStream ioStream);
    
    /** load the whole register from a stream */
    boolean loadFromStream(InputStream ioStream);
}
