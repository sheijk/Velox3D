/*
 * Created on 08.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.model;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

import de.janrehders.gse2.accounts.*;

/**
 * The implementation of the model
 * 
 * @author Jan Rehders
 */
public class ModelImpl implements Model {
    private OrderedRegister myRegister;
    
    public ModelImpl()
    {
        myRegister = new OrderedRegister();
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#addAccount(de.janrehders.gse2.accounts.Account)
     */
    public boolean insert(Account inAccount) {
        return myRegister.insert(inAccount);
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#removeAccount(de.janrehders.gse2.accounts.Account)
     */
    public boolean remove(Account inAccount) {
        return myRegister.remove(inAccount);
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#updateAccount(int, de.janrehders.gse2.accounts.Account)
     */
    public boolean update(int inAccountId, Account inAccount) {
        Account account = this.getById(inAccountId);
        return account.copy(inAccount);
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#accountIterator()
     */
    public AccountIterator accountIterator() {
        return myRegister.iterator();
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#getById(int)
     */
    public Account getById(int inAccountId) {
        AccountIterator iter = myRegister.iterator();
        while(iter.hasNext())
        {
            Account account = iter.next();
            if( account.getAccountNo() == inAccountId )
            {
                return account;
            }
        }

        return null;
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#erase()
     */
    public void scratch() {
        myRegister.scratch();
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#writeToStream(java.io.OutputStream)
     */
    public boolean writeToStream(OutputStream ioStream) {
        boolean succeeded = false;
        
        try {
            ObjectOutputStream str = new ObjectOutputStream(ioStream);
            
            str.writeObject(myRegister);            

            succeeded = true;
        } catch (IOException e) {
            succeeded = false;
            e.printStackTrace(System.err);
        }
        
        return succeeded;
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.model.Model#loadFromStream(java.io.InputStream)
     */
    public boolean loadFromStream(InputStream ioStream) {
        boolean succeeded = false;
        
        try {
            ObjectInputStream str = new ObjectInputStream(ioStream);
            
            myRegister = (OrderedRegister) str.readObject();
            
            succeeded = true;
        } catch (IOException e) {
            e.printStackTrace(System.err);
        } catch (ClassNotFoundException e) {
            e.printStackTrace(System.err);
        }
        
        return succeeded;
    }

}
