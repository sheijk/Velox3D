/*
 * Created on 09.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountVisitor;
import de.janrehders.gse2.accounts.Giro;
import de.janrehders.gse2.accounts.Savings;
import de.janrehders.gse2.accounts.StudentGiro;
import de.janrehders.gse2.controller.Controller;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class StudentGiroEditWindow extends GiroEditWindow {
    private JTextField myRateOfInterestTextField;
    private JButton myStudentIdExpirationDateButton;

    public StudentGiroEditWindow(Controller inController, Account inAccount, boolean inAllowEditing, MainWindow inMainWindow) {
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
        
        // add edit student id controls
        myStudentIdExpirationDateButton = new JButton("...");
        myStudentIdExpirationDateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                if( JOptionPane.showConfirmDialog(
                        StudentGiroEditWindow.this, 
                        "Renew ec card", 
                        "Confirm", 
                        JOptionPane.YES_NO_OPTION
                        ) == JOptionPane.OK_OPTION )
                {
                    StudentGiro studentGiro = getStudentGiro();
                    studentGiro.renewStudentID(null);
                    myStudentIdExpirationDateButton.setText(studentGiro.getStudentIdExpirationDate().toLocaleString());
                }
            }
        });
        inParent.add(horPanel(
                new JLabel("Student id expiration date"), 
                myStudentIdExpirationDateButton));
    }
    
    protected void disableEditing() {
        super.disableEditing();
        
        myRateOfInterestTextField.setEnabled(false);
        myStudentIdExpirationDateButton.setEnabled(false);
    }
    
    protected void applyChanges() {
        super.applyChanges();
        
        StudentGiro studentGiro = getStudentGiro();
        
        if( studentGiro != null )
        {
            try {
                studentGiro.setRateOfInterest(Float.parseFloat(myRateOfInterestTextField.getText()));
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(
                        StudentGiroEditWindow.this,
                        "Rate of interest must be a floating point number");
            }
        }
    }

    protected void updateFromAccount() {
        super.updateFromAccount();
        
        StudentGiro studentGiro = getStudentGiro();
        
        myRateOfInterestTextField.setText(Float.toString(studentGiro.getRateOfInterest()));
        myStudentIdExpirationDateButton.setText(studentGiro.getStudentIdExpirationDate().toLocaleString());
    }

    /** gets the student giro if one with the editors id exists */
    protected StudentGiro getStudentGiro() {
        Account account = getAccount();
        
        if( account != null )
        return (StudentGiro) account.visit(new AccountVisitor() {
            public Object onGiro(Giro inGiro) { return null; }

            public Object onStudentGiro(StudentGiro inGiro) { return inGiro; }

            public Object onSavings(Savings inSavings) { return null; }
        });
        else
            return null;
    }

}
