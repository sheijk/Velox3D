/*
 * Created on 02.04.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.accounts;

import junit.framework.TestCase;

import java.util.Calendar;
import java.util.Date;

/**
 * Tests fuer StudentGiro
 * @author Jan Rehders
 */
public class StudentGiroTests extends TestCase {
	/** vorgegebener test case 1 */
	public void testCopyEqual() {
	    StudentGiro stu2 = new StudentGiro();
	    StudentGiro stu1 = new StudentGiro();
	    assertTrue(stu2.classInvariant());
	    
	    assertTrue(stu1.copy(stu2));
	    assertTrue(stu1.classInvariant());
	    assertTrue(stu1.equals(stu2));
	}
	
	/** vorgegebgener test case 2 */
	public void testTransfer() {
	    StudentGiro stu2 = new StudentGiro();
	    StudentGiro stu1 = new StudentGiro();
	    assertTrue(stu2.classInvariant());
	    
	    assertTrue(stu2.deposit(100));
	    assertTrue(stu1.copy(stu2));
	    assertTrue(stu1.transfer(stu2, 100));
	    assertFalse(stu1.equals(stu2));
	}

	/* Vorbedingung:	StudentGiro studentGiro, Date date
	 * Nachbedingung:	studentGiro.getStudentIdExpirationDate().equals(date)
	 */
	public void testRenewStudentId() {
		StudentGiro studentGiro = new StudentGiro(
				1, new AccountType(1), "tester", 0, 1000, 3, new Date(),
				1.25f, new Date(2005, 10, 1));

		Date date = new Date(2006, 10, 1);
		
		studentGiro.renewStudentID(date);
		
		assertEquals(studentGiro.getStudentIdExpirationDate(), date);		
	}
}
