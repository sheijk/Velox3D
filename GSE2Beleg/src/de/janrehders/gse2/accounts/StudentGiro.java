/*
 * Created on 04.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.util.Calendar;
import java.util.Date;

import net.rehders.gsebeleg1.accounts.AccountType;

/**
 * Giro account for students
 * 
 * @author Jan Rehders
 */
public class StudentGiro extends Giro {
    private float myRateOfInterest;
    private Date myStudentIdExpirationDate;
    
    public StudentGiro()
    {
        super();
        
        myRateOfInterest = 0;
        myStudentIdExpirationDate = new Date();
    }
    
	public StudentGiro(
			final int inAccountNo,
			final AccountType inAccountType,
			final String inOwner,
			final float inBalance,
			final float inDispoCreditLine,
			final int inECNo,
			final Date inECExpirationDate,
			final float inRateOfInterest,
			final Date inStudentIdExpirationDate
			)
	{
		super(inAccountNo, inAccountType, inOwner, inBalance,
				inDispoCreditLine, inECNo, inECExpirationDate);

		myRateOfInterest = inRateOfInterest;
		myStudentIdExpirationDate = (Date)inStudentIdExpirationDate.clone();
	}
    
	public StudentGiro(StudentGiro inSource) {
		super(inSource);
		myRateOfInterest = inSource.myRateOfInterest;
		myStudentIdExpirationDate =
			(Date)inSource.myStudentIdExpirationDate.clone();
	}

	/** clone an object */
	public Account Generate()
	{
	    return new StudentGiro();
	}
	
	/** proof teh class invariant */
	public boolean classInvariant()
	{
	    return super.classInvariant() && classInvariantStudentGiro();
	}
	
	/** check fields of StudentGiro */
	public boolean classInvariantStudentGiro()
	{
	    return myRateOfInterest >= 0 &&
	    		myStudentIdExpirationDate != null;
	}
	
	public boolean equals(StudentGiro inOther) {
	    return super.equals(inOther) &&
	    	myRateOfInterest == inOther.myRateOfInterest &&
	    	myStudentIdExpirationDate.equals(inOther.myStudentIdExpirationDate);
	}
	
	public boolean equals(Object inOther) {
	    if( inOther instanceof StudentGiro ) {
	        return equals((StudentGiro)inOther);
	    }
	    else
	        return false;
	}
	
	/** copy values */
	public void copy(StudentGiro inSource)
	{
	    super.copy(inSource);
	    
	    myRateOfInterest = inSource.myRateOfInterest;
	    myStudentIdExpirationDate = (Date)myStudentIdExpirationDate.clone();
	}
	
	public float getRateOfInterest() {
		return myRateOfInterest;
	}

	public void setRateOfInterest(float inRateOfInterest) {
		myRateOfInterest = inRateOfInterest;
	}

	public Date getStudentIdExpirationDate() {
		return (Date)myStudentIdExpirationDate.clone();
	}

	/**
	 * Neues Enddatum fuer Studentenausweis setzen
	 *
	 * VB: inNewExpirationDate != null und gueltig
	 */
	public void renewStudentID(Date inNewExpirationDate) {
		myStudentIdExpirationDate = (Date)inNewExpirationDate.clone();
	}
	
	/**
	 * Berechnet die aktuellen Zinsen
	 *
	 * VB: inDate != null und inDate liegt nach dem Erstellungsdatum
	 */
	public float calculateBalance(Date inDate) {
		float balance = getBalance();
		final int currentYear = Calendar.getInstance().get(Calendar.YEAR);

		// fuer jedes vergangene jahr
		for(
			int year = getDateOfCreation().getYear();
			year < currentYear;
			++year)
		{
			// erhoehe balance
			balance *= getRateOfInterest();
		}

		return balance;
	}
	
}
