/*
 * Created on 04.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.util.Date;

/**
 * Class for giro accounts
 * 
 * @author Jan Rehders
 */
public class Giro extends Account {
    private float myDispoCreditLine;
    private int myECNo;
    private Date myECExpirationDate;

    /** default c'tor */
    public Giro()
    {
        super();
        
        myDispoCreditLine = 0;
        myECNo = 0;
        renewECCard(myECNo, new Date());
    }
    
	public Giro(
		final int inAccountNo,
		final AccountType inAccountType,
		final String inOwner,
		final float inBalance,
		final float inDispoCreditLine,
		final int inECNo,
		final Date inECExpirationDate
	) {
		super(inAccountNo, inAccountType, inOwner, inBalance);
		
		myDispoCreditLine = inDispoCreditLine;
		renewECCard(inECNo, inECExpirationDate);
	}
	
	/** creates a copy */ 
	public Giro(Giro inSource) {
		super(inSource);
		
		myDispoCreditLine = inSource.myDispoCreditLine;
		myECNo = inSource.myECNo;
		myECExpirationDate = (Date)inSource.myECExpirationDate.clone();
	}
	
	/** clones an object */
	public Account Generate()
	{
	    return new Giro();
	}

	/** checks the classes invariant */
	public boolean classInvariant()
	{
	    return super.classInvariant() && checkGiroClassInvariant();
	}
	
	/** checks the fields of Giro */
	private boolean checkGiroClassInvariant() {
	    return myECExpirationDate != null;
	}

	/** checks if both objects have the same values */
	public boolean equals(Giro inOther) {
	    return 
	    	super.equals(inOther) &&
	    	myECExpirationDate.equals(inOther.myECExpirationDate) &&
	    	myDispoCreditLine == inOther.myDispoCreditLine &&
	    	myECNo == inOther.myECNo;	    		
	}
	
	public boolean equals(Object inOther) {
	    if( inOther instanceof Giro ) {
	        return equals((Giro)inOther);
	    }
	    else
	        return false;
	}
	
	/** copies values from another Giro */
	public void copy(Giro inSource) {
	    super.copy(inSource);
	    
	    myDispoCreditLine = inSource.myDispoCreditLine;
	    myECExpirationDate = (Date)inSource.myECExpirationDate.clone();
	    myECNo = inSource.myECNo;	    
	}

	/** transfer some money to other giro account */
	public boolean transfer(Giro inDest, float inAmount) {
	    if( withdraw(inAmount) ) {
	        return inDest.deposit(inAmount);
	    }
	    else
	        return false;
	}
	
	/** returns the ec card no */
	public int getECCardNo() { return myECNo; }
	/** returns the ec card's expiration date */
	public Date getECCardExpirationDate() { return myECExpirationDate; }
	
	/** renews the ec card */
	public void renewECCard(int inNewECNo, Date inNewECDate) {
		myECNo = inNewECNo;
		// kopieren damit keine unbeabsichtigten veranderungen moeglich sind
		// durch manipilieren des arguments nach dem aufruf des c'tors von
		// ausserhalb
		myECExpirationDate = (Date)inNewECDate.clone();
	}

	/** return the dispo credit line */
	public float getDispoCreditLine() {
		return myDispoCreditLine;
	}
	
	/** set the dispo credit line */
	public void setDispoCreditLine(float inCreditLine) {
	    myDispoCreditLine = inCreditLine;
	}

	/** 
	 * Geldsumme abheben
	 * 
	 * VB: myBalance - inAmount > - myDispoCreditLine
	 * NB: myBalance wurde um inAmount verringert 
	 */
	public boolean withDraw(float inAmount) {
		if( getBalance() - inAmount < - myDispoCreditLine ) {
			return false;
		}
		else {
			super.withdraw(inAmount);
			return true;
		}
	}

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#generate()
     */
    public Account generate() {
        // TODO Auto-generated method stub
        return null;
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#visit(de.janrehders.gse2.accounts.AccountVisitor)
     */
    public Object visit(AccountVisitor inVisitor) {
        return inVisitor.onGiro(this);
    }
}
