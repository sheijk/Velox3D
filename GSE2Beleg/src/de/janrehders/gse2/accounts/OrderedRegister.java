/*
 * Created on 04.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.io.Serializable;
import java.util.Date;
import java.util.Iterator;
import java.util.TreeSet;

/**
 * A ordered register of accounts
 * 
 * @author Jan Rehders
 */
public class OrderedRegister implements Serializable {
    private String myRegisterInformation;
    private Date myDateOfCreation;
    private TreeSet myAccounts;

    public OrderedRegister()
    {
        this("");
    }
    
    public OrderedRegister(String inInformation)
    {
        myRegisterInformation = inInformation;
        myDateOfCreation = new Date();
        myAccounts = new TreeSet();
    }
    
    public OrderedRegister Generate()
    {
        return new OrderedRegister();
    }
    
    public boolean classInvariant()
    {
        return myRegisterInformation != null &&
        		myDateOfCreation != null &&
        		myAccounts != null;
    }
    
    public boolean equalIdentity(OrderedRegister inOther)
    {
        return this == inOther;
    }
    
    public boolean equals(OrderedRegister inOther)
    {
        return myRegisterInformation.equals(inOther.myRegisterInformation) &&
        		myDateOfCreation.equals(inOther.myDateOfCreation) &&
        		myAccounts.equals(inOther.myAccounts);
    }
    
//    public void copy(OrderedRegister inSource)
//    {
//        myRegisterInformation = inSource.myRegisterInformation;
//        myDateOfCreation = (Date)myDateOfCreation.clone();
//        myAccounts = (TreeSet)inSource.myAccounts.clone();
//    }
    
    /** returns true if the give account is contained within the register */
    public boolean find(Account inAccount)
    {
        return myAccounts.contains(inAccount);
    }
    
    public String getRegisterInformation() { return myRegisterInformation; }
    public void setRegisterInformation(String i) { myRegisterInformation = i; }
    
    public Date getDateOfCreation() { return myDateOfCreation; }
    
    public int card() { return myAccounts.size(); }
    
    /** add an account */
    public boolean insert(Account inAccount)
    {
        return myAccounts.add(inAccount);
    }
    
    /** remove an account */
    public boolean remove(Account inAccount)
    {
        return myAccounts.remove(inAccount);
    }
    
    /** remove all accounts */
    public boolean scratch()
    {
        myAccounts.clear();
        return true;
    }
    
    /** returns an iterator to iterate all accounts */
    public AccountIterator iterator()
    {
        final Iterator iter = myAccounts.iterator();
        
        return new AccountIterator()
        {
            public Account next() {
                return (Account) iter.next();
            }

            public boolean hasNext() {
                return iter.hasNext();
            }
        };    
    }

    /**
     * @param out_reg2
     * @return
     */
    public boolean copy(OrderedRegister inSource) {
        myAccounts = (TreeSet) inSource.myAccounts.clone();
        myDateOfCreation = (Date) inSource.myDateOfCreation.clone();
        myRegisterInformation = inSource.myRegisterInformation;
        
        return true;        
    }
}
