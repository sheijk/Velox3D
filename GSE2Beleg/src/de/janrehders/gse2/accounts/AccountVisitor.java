/*
 * Created on 08.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

/**
 * A visitor for visiting an account. 
 * Use account.visit(new AccountVisitor() {..}) to execute specific code for
 * different subtypes of account
 * 
 * @author Jan Rehders
 */
public interface AccountVisitor {
    Object onGiro(Giro inGiro);
    Object onStudentGiro(StudentGiro inGiro);
    Object onSavings(Savings inSavings);
}
