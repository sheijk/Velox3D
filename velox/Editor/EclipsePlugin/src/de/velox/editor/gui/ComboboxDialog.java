package de.velox.editor.gui;

import java.util.Collection;

import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.custom.CCombo;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;

public class ComboboxDialog {
	public static final int CANCEL = 0;

	private Shell sShell = null;  //  @jve:decl-index=0:visual-constraint="15,8"
	private CCombo inputCombo = null;
	private Button okButton = null;
	private Button cancelButton = null;
	private Label messageLabel = null;
	
	private final String myTitle;
	private final String myMessage;
	private String myValue = null;
	private final String myInitialValue;
	private final Collection<String> myOptions;
	private final Shell myParent;
	
	public ComboboxDialog(Shell shell,
			String title, String message, String defaultValue,
			Collection<String> options)
	{
		myParent = shell;
		
		myTitle = title;
		myMessage = message;
		myInitialValue = defaultValue;
		myOptions = options;
	}
	
	public String open()
	{
		createSShell();
		sShell.setVisible(true);
		sShell.open();
		while( ! sShell.isDisposed() ) 
		{
			if( !myParent.getDisplay().readAndDispatch() )
				myParent.getDisplay().sleep();
		}
				
		return myValue;
	}

	/**
	 * This method initializes sShell
	 */
	protected void createSShell() {
		sShell = new Shell(myParent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		sShell.setText(myTitle);
		sShell.setSize(new org.eclipse.swt.graphics.Point(293,144));
		inputCombo = new CCombo(sShell, SWT.NONE);
		inputCombo.setText(myInitialValue);
		for(String option : myOptions)
		{
			inputCombo.add(option);
		}
		inputCombo.setBounds(new org.eclipse.swt.graphics.Rectangle(26,45,240,17));
		okButton = new Button(sShell, SWT.NONE);
		okButton.setBounds(new org.eclipse.swt.graphics.Rectangle(101,75,76,23));
		okButton.setText("&Ok");
		cancelButton = new Button(sShell, SWT.NONE);
		cancelButton.setBounds(new org.eclipse.swt.graphics.Rectangle(191,75,76,23));
		cancelButton.setText("&Cancel");
		messageLabel = new Label(sShell, SWT.NONE);
		messageLabel.setBounds(new org.eclipse.swt.graphics.Rectangle(26,15,241,13));
		messageLabel.setText(myMessage);

		Listener buttonListener = new Listener() {
			public void handleEvent(Event event) {
				if( event.widget == okButton )
					myValue = inputCombo.getText();
				else
					myValue = null;
				
				sShell.close();
			}
		};
		
		okButton.addListener(SWT.Selection, buttonListener);
		cancelButton.addListener(SWT.Selection, buttonListener);
	}
}
