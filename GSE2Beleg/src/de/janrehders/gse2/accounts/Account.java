/*
 * Created on 29.07.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;

/**
 * Base class for all accounts
 * 
 * @author Jan Rehders
 */
public abstract class Account implements Comparable, Serializable {
    private int myAccountNo = getNewAccountId();
    private Date myDateOfCreation = new Date();
    private AccountType myType;
    private String myOwner;
    private float myBalance = 0;
    
    private static int ourLastAccountId = 1;
    
    private static int getNewAccountId()
    {
        return ++ourLastAccountId;
    }
    
    /** creates a default account */
    public Account() {
//        myAccountNo = -1;
        myType = AccountType.invalid();
        myOwner = "";
        myBalance = 0;
    }
    
    /** inits the account with the given values */
    public Account(int inNumber, AccountType inType, String inOwner, float inBalance) {
//        myAccountNo = inNumber;
        myType = inType;
        myOwner = inOwner;
        myBalance = inBalance;
    }
    
    /** creates a copy */
    public Account(Account inSource) {
        this();
        copy(inSource);
    }
    
    /** clones an object */
    public abstract Account generate();
    
    /** proves the class invariant */
    public boolean classInvariant() {
        return classInvariantAccount();
    }
    
    /** prooves the class invariant for all fields of Account */
    private boolean classInvariantAccount() {
        return 
	    	myAccountNo > 0 &&
	    	myDateOfCreation != null &&
	    	myType != null &&
	    	myOwner != null; 
    }
    
    /** returns true if both object identities are equal */
    public boolean equalIdentity(Account inOther) {
        return this == inOther;
    }
    
    /** returns whether both account's values are equal */
    public boolean equals(Account inOther) {
        return
        	myAccountNo == inOther.myAccountNo &&
        	myDateOfCreation.equals(inOther.myDateOfCreation) &&
        	myAccountNo == inOther.myAccountNo &&
        	myBalance == inOther.myBalance &&
        	myOwner.equals(inOther.myOwner) &&
        	myType.equals(inOther.myType);
    }

    /** returns whether both object have the same values */
    public boolean equals(Object inOther) {
        if( inOther instanceof Account ) {
            return this.equals((Account)inOther);
        }
        else {
            return false;
        }
    }
    
    /** returns whether both accounts have the same key */
    public boolean equalKey(Account inOther) {
        return myAccountNo == inOther.myAccountNo;
    }
    
    /** copies values from the given account if possible */
    public boolean copy(Account inSource) {
        myAccountNo = inSource.myAccountNo;
        myDateOfCreation = inSource.myDateOfCreation;
        myType = inSource.myType;
        myOwner = inSource.myOwner;
        myBalance = inSource.myBalance;
        
        return true;
    }

    /** returns the key */
    public String keyOf() {
        return Integer.toString(myAccountNo);
    }
    
    /** compares both object, -1 if this < o, 1 if this > o, 0 if this == o */
    public int compareTo(Account inOther) {
        if( myAccountNo < inOther.myAccountNo )
            return -1;
        if( myAccountNo > inOther.myAccountNo )
            return 1;
        else
            return 0;
    }

    /* (non-Javadoc)
     * @see java.lang.Comparable#compareTo(java.lang.Object)
     */
    public int compareTo(Object inOther) {
		return compareTo((Account)inOther);
    }

    /** returns the account's unique number */    
    public int getAccountNo() { return myAccountNo; }
    /** returns the date of creation */
    public Date getDateOfCreation() { return myDateOfCreation; }
    /** returns the accounts type */
    public AccountType getType() { return myType; }
    /** changes the account's type */
    public void setType(AccountType inType) { myType = inType; }
    /** returns the account's owner */
    public String getOwner() { return myOwner; }
    /** changes the owner */
    public void setOwner(String inOwner) { myOwner = inOwner; }
    /** return the account's balance */
    public float getBalance() { return myBalance; }
    /** set accounts balance */
    public void setBalance(float inBalance) { myBalance = inBalance; }
    
    /** deposits money to the account */
    public boolean deposit(float inAmount) {
        if( inAmount >= 0 ) {
            myBalance += inAmount;
            return true;
        }
        else
            return false;
    }
    
    /** withdraws money from the account */
    public boolean withDraw(float inAmount) {
        if( inAmount > 0 ) {
            myBalance -= inAmount;
            return true;
        }
        else
            return false;
    }
    
    /** determine exact type of account */
    public abstract Object visit(AccountVisitor inVisitor);
    
    /** gets a short string identifying the account type */
    public final String getTypeString()
    {
        return (String)visit(new AccountVisitor() {
            public Object onGiro(Giro inGiro) {
                return "Giro";
            }

            public Object onStudentGiro(StudentGiro inGiro) {
                return "StudentGiro";
            }

            public Object onSavings(Savings inSavings) {
                return "Savings";
            }
        });
    }

    private void readObject(ObjectInputStream in)
    	throws IOException, ClassNotFoundException
    {
        in.defaultReadObject();
        
        // assign a new, unused account id
        myAccountNo = Account.getNewAccountId();
    }
    
    /** print's the accounts fields to the standard output stream */
    public void show() {
        System.out.println("Account no.: " + myAccountNo);
        System.out.println("Balance: " + myBalance);
        System.out.println("Owner: " + myOwner);
        System.out.println("Creation date: " + myDateOfCreation);
        System.out.println("Type: " + myType);
    }
}
