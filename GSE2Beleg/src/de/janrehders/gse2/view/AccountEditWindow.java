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
    private final Account myAccount;
    private final Controller myController;
    
    private TextField myOwnerTextField;

    public AccountEditWindow(
            Controller inController, 
            Account inAccount,
            boolean inAllowEditing,
            MainWindow inMainWindow
            )
    {
        super(getHeader(inAccount), inMainWindow);

        assert inController != null;
        assert inAccount != null;
        
        myAccount = inAccount;
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
        }
        // if editing is enabled, add editing functionality
        else
        {
            JButton btn = new JButton("Apply");
            btn.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent out_e) {
                    // apply changes
                    myAccount.setOwner(myOwnerTextField.getText());
                    
                    // notify controller
                    myController.getModel().updateAccount(myAccount.getAccountNo(), myAccount);
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
                new Label("" + myAccount.getAccountNo())
                ));
        
        myOwnerTextField = new TextField();
        inParent.add(horPanel(
                new Label("Owner"),
                myOwnerTextField
                ));
    }
            
    private void updateFromAccount()
    {
        myOwnerTextField.setText(myAccount.getOwner());
    }
    
    private static String getHeader(Account inAccount)
    {
        assert inAccount != null;
        return "Account nr. " + inAccount.getAccountNo();
    }
}
