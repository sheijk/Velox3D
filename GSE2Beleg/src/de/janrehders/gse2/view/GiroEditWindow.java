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

import de.janrehders.gse2.accounts.*;
import de.janrehders.gse2.controller.Controller;

/**
 * A dialog to edit giro accounts
 * 
 * @author Jan Rehders
 */
public class GiroEditWindow extends AccountEditWindow {
    private JTextField myDispoCreditLineTextControl;
    private JLabel myEcNoLabel;
    private JButton myEcExporationDateButton;
    
    /** creates a window for editing a giro account */
    public GiroEditWindow(Controller inController, Account inAccount, boolean inAllowEditing, MainWindow inMainWindow) {
        super(inController, inAccount, inAllowEditing, inMainWindow);
        
    }
    
    protected void buildUI(Container inParent) {
        super.buildUI(inParent);

        // add giro controls
        myDispoCreditLineTextControl = new JTextField();
        myDispoCreditLineTextControl.setInputVerifier(new FloatInputVerifier());
        
        inParent.add(horPanel(
                new JLabel("Dispo credit line"),
                myDispoCreditLineTextControl));
        
        myEcNoLabel = new JLabel("");
        inParent.add(horPanel(new JLabel("Ec card no."), myEcNoLabel));

        myEcExporationDateButton = new JButton("...");
        myEcExporationDateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                if( JOptionPane.showConfirmDialog(
                        GiroEditWindow.this, 
                        "Renew ec card", 
                        "Confirm", 
                        JOptionPane.YES_NO_OPTION
                        ) == JOptionPane.OK_OPTION )
                {
                    Giro giro = getGiro();
                    if( giro != null )
                    {
                        giro.renewECCard(-1, null);
                        myEcNoLabel.setText(Integer.toString(giro.getECCardNo()));
                        myEcExporationDateButton.setText(giro.getECCardExpirationDate().toLocaleString());
                    }
                }
            }
        });
        
        inParent.add(horPanel(new JLabel("Ec expiration date"), myEcExporationDateButton));
    }
    
    protected void disableEditing() {
        super.disableEditing();
        
        myDispoCreditLineTextControl.setEnabled(false);
        myEcExporationDateButton.setEnabled(false);
    }

    protected void updateFromAccount() {
        super.updateFromAccount();
        
        Giro giro = getGiro();
        
        if( giro != null )
        {
            myDispoCreditLineTextControl.setText(Float.toString(giro.getDispoCreditLine()));
            
            myEcNoLabel.setText(Integer.toString(giro.getECCardNo()));
            myEcExporationDateButton.setText(giro.getECCardExpirationDate().toLocaleString());
        }
        else
            close();
    }

    protected void applyChanges() {
        super.applyChanges();

        Giro giro = getGiro();
        
        if( giro != null )
        try {
            giro.setDispoCreditLine(Float.parseFloat(myDispoCreditLineTextControl.getText()));
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Invalid format in dispo credit line");
        }
        else
            close();
    }

    /** 
     * gets the giro account with the dialog's id or null if no giro with such
     * id exists
     */
    private Giro getGiro()
    {
        Account account = getAccount();
        
        if( account != null )
        return (Giro)account.visit(new AccountVisitor() {
            public Object onGiro(Giro inGiro) { return inGiro; }

            public Object onStudentGiro(StudentGiro inGiro) { return inGiro; }

            public Object onSavings(Savings inSavings) { return null; }
        });
        else
            return null;
    }
}
