/*
 * Created on 07.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.*;
import java.awt.event.*;
import java.util.Observable;
import java.util.Observer;

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
public abstract class AccountEditWindow extends Document {
    private final Controller myController;
    private final int myAccountId;
    
    private JTextField myOwnerTextField;
    private JTextField myBalanceTextField;
    private JLabel myDateOfCreationLabel;

    protected AccountEditWindow(
            Controller inController, 
            Account inAccount,
            boolean inAllowEditing,
            MainWindow inMainWindow
            )
    {
        super(getHeader(inAccount, inAllowEditing), inMainWindow);

        assert inController != null;
        assert inAccount != null;
        
        myAccountId = inAccount.getAccountNo();
        myController = inController;
        
        // setup ui
        setSize(400, 300);

        BoxLayout layout = new BoxLayout(getContentPane(), BoxLayout.Y_AXIS);
        getContentPane().setLayout(layout);
        
        buildUI(getContentPane());
        
        // if editing is disabled, deactivate all edit controls
        if( inAllowEditing == false )
        {
            disableEditing();
        }
        // if editing is enabled, add editing functionality
        else
        {
            JButton btn = new JButton("Apply");
            btn.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent out_e) {
                    applyChanges();

                    // notify controller
                    myController.getModel().update(getAccount().getAccountNo(), getAccount());
                }
            });
            
            getContentPane().add(btn);
        }
        
        // register as controller listener
        inController.addObserver(new Observer() {
            public void update(Observable out_o, Object out_arg) {
                updateFromAccount();
            }
        });
        
        updateFromAccount();
        
        show();
    }

    /**
     * 
     */
    protected void disableEditing() {
        myOwnerTextField.setEnabled(false);
        myBalanceTextField.setEnabled(false);
    }

    protected static JPanel horPanel(Component inLeft, Component inRight)
    {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
        
        panel.add(inLeft);
        panel.add(inRight);
        
        return panel;
    }
    
    protected void buildUI(final Container inParent)
    {
        inParent.add(horPanel(
                new JLabel("Account no."), 
                new JLabel("" + getAccount().getAccountNo())
                ));
        
        myOwnerTextField = new JTextField();
        inParent.add(horPanel(
                new JLabel("Owner"),
                myOwnerTextField
                ));

        myBalanceTextField = new JTextField();
        myBalanceTextField.setInputVerifier(new FloatInputVerifier());
        
        inParent.add(horPanel(
                new JLabel("Balance"),
                myBalanceTextField));
        
        myDateOfCreationLabel = new JLabel(getAccount().getDateOfCreation().toLocaleString());
        inParent.add(horPanel(
                new JLabel("Date of creation"),
                myDateOfCreationLabel));
        
        //TODO: combobox for type
        
    }
    
    protected void updateFromAccount()
    {
        // close if account does not exist anymore
        if( getAccount() == null )
        {
            System.out.println("closing");
            
            close();            
        }
        else
        {
            Account account = getAccount();
            
            myOwnerTextField.setText(account.getOwner());
            myBalanceTextField.setText(Float.toString(account.getBalance()));
            myDateOfCreationLabel.setText(account.getDateOfCreation().toLocaleString());
        }
    }
    
    private static String getHeader(Account inAccount, boolean inAllowEditing)
    {
        assert inAccount != null;
        String title = inAllowEditing ? "Edit " : "View ";
        title += inAccount.getTypeString() + " nr. " + inAccount.getAccountNo();
        
        return title;        	
    }

    /**
     * @return Returns the account.
     */
    protected Account getAccount() {
        return myController.getModel().getById(myAccountId);
    }

    protected void applyChanges() {
        // apply changes
        Account account = getAccount();
        try {
            account.setBalance(Float.parseFloat(myBalanceTextField.getText()));
            account.setOwner(myOwnerTextField.getText());
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(AccountEditWindow.this,
                    "Enter a valid floating point number for balance");
        }
    }

    protected static final class FloatInputVerifier extends InputVerifier {
        public boolean verify(JComponent input) {
            try {
                Float.parseFloat(((JTextField)input).getText());
                return true;
            } catch (NumberFormatException e) {
                return false;
            }
        }
    }
}
