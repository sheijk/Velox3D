/*
 * Created on 09.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.Container;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountVisitor;
import de.janrehders.gse2.accounts.Giro;
import de.janrehders.gse2.accounts.Savings;
import de.janrehders.gse2.accounts.StudentGiro;
import de.janrehders.gse2.controller.Controller;
import de.janrehders.gse2.view.AccountEditWindow.FloatInputVerifier;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class SavingsEditWindow extends AccountEditWindow {
    private JTextField myRateOfInterestTextField;

    protected SavingsEditWindow(Controller inController, Account inAccount, boolean inAllowEditing, MainWindow inMainWindow) {
        super(inController, inAccount, inAllowEditing, inMainWindow);
    }

    protected void buildUI(Container inParent) {
        super.buildUI(inParent);
        
        // add edit field for rate of interest
        myRateOfInterestTextField = new JTextField();
        myRateOfInterestTextField.setInputVerifier(new FloatInputVerifier());
        inParent.add(horPanel(
                new JLabel("Rate of interest"), 
                myRateOfInterestTextField));
    }
    
    protected void disableEditing() {
        super.disableEditing();

        myRateOfInterestTextField.setEnabled(false);
    }

    protected void applyChanges() {
        super.applyChanges();

        Savings savings = getSavings();
        
        if( savings != null )
        {
            try {
                savings.setRateOfInterest(Float.parseFloat(myRateOfInterestTextField.getText()));
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(
                        SavingsEditWindow.this,
                        "Rate of interest must be a floating point number");
            }
        }
    }
    
    protected void updateFromAccount() {
        super.updateFromAccount();

        Savings savings = getSavings();
        
        if( savings != null )
        {
            myRateOfInterestTextField.setText(Float.toString(savings.getRateOfInterest()));
        }
        else
            close();
    }

    private Savings getSavings() {
        Account account = getAccount();
        
        if( account != null )
        return (Savings)account.visit(new AccountVisitor() {
            public Object onGiro(Giro inGiro) { return null; }

            public Object onStudentGiro(StudentGiro inGiro) { return null; }
            
            public Object onSavings(Savings inSavings) { return inSavings; }
        });
        else
            return null;
    }
}
