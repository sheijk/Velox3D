/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/**
 * 
 */
package de.velox.editor.widgets;

import java.util.Collection;
import java.util.LinkedList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class FilterDialog extends Dialog {
	private String result = null;
	
	public FilterDialog(Shell parent, String title, Collection<String> options) {
		super(parent);
		this.options.addAll(options);
	}
	
	private final LinkedList<String> options = new LinkedList<String>();
	
	public void addOption(String option) {
		options.add(option);
	}
	
	public String open() {
		Shell parent = getParent();
		final Shell shell = new Shell(parent);
		RowLayout layout = new RowLayout(SWT.VERTICAL);
		shell.setLayout(layout);
		
		final FilterPane pane = new FilterPane(shell, 
			SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		pane.setSize(400, 300);
		
		for(String option : options) {
			pane.addOption(option);
		}
		
		Composite buttonComp = new Composite(shell, SWT.NONE);
		buttonComp.setLayout(new FillLayout());
		
		Button okButton = new Button(buttonComp, SWT.NONE);
		okButton.setText("&Ok");
		okButton.addSelectionListener(new SelectionListener() {
			public void widgetDefaultSelected(SelectionEvent e) {
				widgetSelected(e);
			}
		
			public void widgetSelected(SelectionEvent e) {
				result = pane.getSelectedOption();
				shell.dispose();				
			}		
		});
		
		Button cancelButton = new Button(buttonComp, SWT.NONE);
		cancelButton.setText("&Cancel");
		cancelButton.addSelectionListener(new SelectionListener() {
			public void widgetDefaultSelected(SelectionEvent e) {
				widgetSelected(e);
			}
		
			public void widgetSelected(SelectionEvent e) {
				result = null;
				shell.dispose();
			}
		});
		
		shell.pack();	
		shell.open();
		Display display = parent.getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) display.sleep();
		}
		
		return result;
	}
}
