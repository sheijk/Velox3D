/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.controller;

import java.util.Observable;
import java.util.Observer;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountIterator;
import de.janrehders.gse2.model.Model;

/**
 * The controller of the application 
 * @author Jan Rehders
 */
public class Controller extends Observable {
    private final ObservedModel myModel;
    
    public Controller(Model inModel)
    {
        myModel = new ObservedModel(inModel);
    }

    /** returns the model */
    public Model getModel()
    {
        return myModel;
    }
    
    /** notifies all observers of an update */
    private void notifyUpdate()
    {
        setChanged();
        notifyObservers();    
    }
    
    private class ObservedModel implements Model
    {
        private final Model myDelegate;
        
        public ObservedModel(Model inDelegate)
        {
            myDelegate = inDelegate;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#addAccount(de.janrehders.gse2.accounts.Account)
         */
        public boolean addAccount(Account inAccount) {
            if( myDelegate.addAccount(inAccount) )
            {
                notifyUpdate();
                
                return true;
            }
            else
                return false;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#removeAccount(de.janrehders.gse2.accounts.Account)
         */
        public boolean removeAccount(Account inAccount) {
            if( myDelegate.removeAccount(inAccount) )
            {
                notifyUpdate();
                return true;
            }
            else
                return false;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#updateAccount(int, de.janrehders.gse2.accounts.Account)
         */
        public boolean updateAccount(int inAccountId, Account inAccount) {
            if( myDelegate.updateAccount(inAccountId, inAccount) )
            {
                notifyUpdate();
                return true;
            }
            else
                return false;
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#accountIterator()
         */
        public AccountIterator accountIterator() {
            return myDelegate.accountIterator();
        }

        /* (non-Javadoc)
         * @see de.janrehders.gse2.model.Model#getById(int)
         */
        public Account getById(int inAccountId) {
            return myDelegate.getById(inAccountId);
        }
    }
}
