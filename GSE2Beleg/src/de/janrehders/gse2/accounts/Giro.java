/*
 * Created on 04.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.util.Calendar;
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
    
    private static int ourLastECCardNo = 0;

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
	public boolean copy(Account inSource) {
	    if( inSource instanceof Giro && super.copy(inSource) )
	    {
	        Giro inGiroSource = (Giro)inSource;
	        
		    myDispoCreditLine = inGiroSource.myDispoCreditLine;
		    myECExpirationDate = (Date)inGiroSource.myECExpirationDate.clone();
		    myECNo = inGiroSource.myECNo;
		    
		    return true;
	    }
	    else
	        return false;
	}

	/** transfer some money to other giro account */
	public boolean transfer(Giro inDest, float inAmount) {
	    if( withDraw(inAmount) ) {
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
	    // if an invalid number is given, generate a new unused one
	    if( inNewECNo >= 0 )
	    {
	        myECNo = inNewECNo;
	    }
	    else
	    {
	        myECNo = ++ourLastECCardNo;
	    }

	    // if no date is specified, renew for one year
	    if( inNewECDate == null )
	    {
	        inNewECDate = datePlusOneYear(myECExpirationDate);        
	    }
	    
		// kopieren damit keine unbeabsichtigten veranderungen moeglich sind
		// durch manipilieren des arguments nach dem aufruf des c'tors von
		// ausserhalb
		myECExpirationDate = (Date)inNewECDate.clone();
	}

	/**
     * @param inDate
	 * @return
     */
    protected static Date datePlusOneYear(Date inDate) {
        Date inNewECDate;
        Calendar cal = Calendar.getInstance();
        cal.setTime(inDate);
        cal.add(Calendar.YEAR, 1);
        
        inNewECDate = cal.getTime();
        return inNewECDate;
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
			super.withDraw(inAmount);
			return true;
		}
	}

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#generate()
     */
    public Account generate() {
        return new Giro();        
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#visit(de.janrehders.gse2.accounts.AccountVisitor)
     */
    public Object visit(AccountVisitor inVisitor) {
        return inVisitor.onGiro(this);
    }
}
