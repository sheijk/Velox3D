/*
 * Created on 03.04.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;


/**
 * Konkrete von Account abgeleitete Klasse. Da Account abstract ist und
 * daher keine Instanz davon erzeugt werden kann wird hier eine Klasse
 * von Account abgeleitet welche das Verhalten von Account nicht veraenedert
 * und zum Testen benutzt wird
 * 
 * @author Jan Rehders
 */
public class TestAccount extends Account {
	/** delegiert an account c'tor */
	public TestAccount(
			int inNo, 
			AccountType inType,
			String inOwner,
			float inBalance
	) {
		super(inNo, inType, inOwner, inBalance);
	}
	
	/** delegiert an den account c'tor */
	protected TestAccount(Account inSource) {
		super(inSource);
	}

	/** erzeugt account mit nummer id */
	public TestAccount(int inId) {
		super(inId, new AccountType(1), "blub", 0);
	}

	/** erzeugt TestAccount mit Standardwerten */
	public TestAccount() {
		this(2353);
	}

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#generate()
     */
    public Account generate() {
        return new TestAccount();
    }

    /* (non-Javadoc)
     * @see de.janrehders.gse2.accounts.Account#visit(de.janrehders.gse2.accounts.AccountVisitor)
     */
    public Object visit(AccountVisitor inVisitor) {
        return null;
    }
}