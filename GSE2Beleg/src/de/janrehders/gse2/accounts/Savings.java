/*
 * Created on 04.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

/**
 * @author Jan Rehders
 */
public class Savings extends Account {
	private float myRateOfInterest;

	public Savings()
	{
	    super();
	    
	    myRateOfInterest = 0;
	}

	public Savings(
		final int inAccountNo,
		final AccountType inAccountType,
		final String inOwner,
		final float inBalance,
		final float inRateOfInterest
		)
	{
		super(inAccountNo, inAccountType, inOwner, inBalance);
		myRateOfInterest = inRateOfInterest;
	}

	public Savings(Savings inSource) {
		super(inSource);

		myRateOfInterest = inSource.myRateOfInterest;
	}
	
	/** create new instnace */
	public Account Generate()
	{
	    return new Savings();
	}
	
	public boolean classInvariant()
	{
	    return super.classInvariant() && classInvariantSavings();
	}
	
	public boolean classInvariantSavings()
	{
	    return myRateOfInterest >= 0;
	}
	
	public boolean equals(Savings inOther) 
	{
	    return super.equals(inOther) &&
	    		myRateOfInterest == inOther.myRateOfInterest;
	}
	
	public boolean equals(Object inOther)
	{
	    if( inOther instanceof Savings ) {
	        return equals((Savings)inOther);
	    }
	    else
	        return false;
	}
	
	public void copy(Savings inOther)
	{
	    super.copy(inOther);
	    
	    myRateOfInterest = inOther.myRateOfInterest;
	}
	
	public float getRateOfInterest() {
		return myRateOfInterest;
	}

	public void setRateOfInterest(float inRateOfInterest) {
		myRateOfInterest = inRateOfInterest;
	}
	
	public void show()
	{
	    super.show();
		System.out.println("Rate of interest: " + myRateOfInterest);
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
        return inVisitor.onSavings(this);
    }
}
