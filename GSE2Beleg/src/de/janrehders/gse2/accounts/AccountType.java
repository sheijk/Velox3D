/*
 * Created on 29.07.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import java.io.Serializable;

/**
 * Stellt den Typ eines Accounts dar.
 * 
 * @author sheijk
 */
public class AccountType implements Serializable {
    /** creates a commercial account type */
    public static AccountType commercial() {
        return new Commercial();        
    }
    
    /** creates a private account type */
    public static AccountType privat() {
        return new Private();
    }
    
    /** creates an invalid account type */
    public static AccountType invalid() {
        return new Invalid();
    }
    
    public final static int INVALID_ID = 0;
    public final static int COMMERCIAL_ID = 1;
    public final static int PRIVATE_ID = 2;
    
    private final int myId;
    
    /** protected c'tor */
    protected AccountType(int id) {
        myId = id;
    }
    
    /** gives the type id, can be either COMMERCIAL_ID or PRIVATE_ID */
    public int getTypeId() {
        return myId;
    }

    /** returns whether the account type is commercial */
    public boolean isCommercial() {
        return COMMERCIAL_ID == myId;
    }
    
    /** returns whether the account type is private */
    public boolean isPrivate() {
        return PRIVATE_ID == myId;
    }
    
    /** a commercial account type */
    private static class Commercial extends AccountType {
        Commercial() { super(COMMERCIAL_ID); }
	}
    
    /** a private account type */
    private static class Private extends AccountType {
        Private() { super(PRIVATE_ID); }
    }
    
    /** an invalid account type */
    private static class Invalid extends AccountType {
        Invalid() { super(INVALID_ID); }
    }
}
