/*
 * Created on 13.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2;

import de.janrehders.gse2.accounts.AccountTests;
import de.janrehders.gse2.accounts.GiroTests;
import de.janrehders.gse2.accounts.OrderedRegisterTests;
import de.janrehders.gse2.accounts.SavingsTests;
import de.janrehders.gse2.accounts.StudentGiroTests;
import de.janrehders.gse2.controller.ControllerTests;
import junit.framework.Test;
import junit.framework.TestSuite;

/**
 * Fuehrt alle Tests des Models und des Controllers durch
 * @author Jan Rehders
 */
public class AllTests {
    public static void main(String[] args) {
        junit.textui.TestRunner.run(AllTests.suite());
    }

    public static Test suite() {
        TestSuite suite = new TestSuite("Test for model and controller");
        //$JUnit-BEGIN$
        suite.addTestSuite(AccountTests.class);
        suite.addTestSuite(GiroTests.class);
        suite.addTestSuite(StudentGiroTests.class);
        suite.addTestSuite(SavingsTests.class);
        suite.addTestSuite(OrderedRegisterTests.class);
        suite.addTestSuite(ControllerTests.class);
        //$JUnit-END$
        return suite;
    }
}
