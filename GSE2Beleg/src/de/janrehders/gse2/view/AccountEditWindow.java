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
import de.janrehders.gse2.controller.Controller;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class AccountEditWindow extends Document {
//    private final Account myAccount;
    private final Controller myController;
    private final int myAccountId;
    
    private JTextField myOwnerTextField;
    private JTextField myBalanceTextField;
    private JLabel myDateOfCreationLabel;

    public AccountEditWindow(
            Controller inController, 
            Account inAccount,
            boolean inAllowEditing,
            MainWindow inMainWindow
            )
    {
        super(getHeader(inAccount, inAllowEditing), inMainWindow);

        assert inController != null;
        assert inAccount != null;
        
//        myAccount = inAccount;
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
            myOwnerTextField.setEnabled(false);
            myBalanceTextField.setEnabled(false);
        }
        // if editing is enabled, add editing functionality
        else
        {
            JButton btn = new JButton("Apply");
            btn.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent out_e) {
                    // apply changes
                    Account account = getAccount();
                    try {
                        account.setBalance(Float.parseFloat(myBalanceTextField.getText()));
                        account.setOwner(myOwnerTextField.getText());
                        // notify controller
                        myController.getModel().update(getAccount().getAccountNo(), getAccount());
                    } catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(AccountEditWindow.this,
                                "Enter a valid floating point number for balance");
                    }
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

    private JPanel horPanel(Component inLeft, Component inRight)
    {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
        
        panel.add(inLeft);
        panel.add(inRight);
        
        return panel;
    }
    
    private void buildUI(Container inParent)
    {
        inParent.add(horPanel(
                new Label("Account no."), 
                new Label("" + getAccount().getAccountNo())
                ));
        
        myOwnerTextField = new JTextField();
        inParent.add(horPanel(
                new Label("Owner"),
                myOwnerTextField
                ));

        myBalanceTextField = new JTextField();
        myBalanceTextField.setInputVerifier(new InputVerifier() {
            public boolean verify(JComponent input) {
                try {
                    Float.parseFloat(((JTextField)input).getText());
                    return true;
                } catch (NumberFormatException e) {
                    return false;
                }
            }
        });
        
        inParent.add(horPanel(
                new Label("Balance"),
                myBalanceTextField));
        
        myDateOfCreationLabel = new JLabel(getAccount().getDateOfCreation().toLocaleString());
        inParent.add(horPanel(
                new Label("Date of creation"),
                myDateOfCreationLabel));
        
        //TODO: combobox for type
    }
            
    private void updateFromAccount()
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
    private Account getAccount() {
        return myController.getModel().getById(myAccountId);
    }
}
