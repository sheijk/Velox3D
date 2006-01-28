package de.velox.editor.widgets;

import java.util.LinkedList;

import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.GridData;

import sun.net.dns.ResolverConfiguration.Options;
import org.eclipse.swt.custom.ScrolledComposite;

public class FilterPane extends Composite {

	private Text text = null;
	private List optionList = null;
		
	public FilterPane(Composite parent, int style) {
		super(parent, style);
		initialize();
	}

	private LinkedList<String> options = new LinkedList<String>();

	public void addOption(String opt) {
		options.add(opt);
		optionList.add(opt);
	}
	
	public String getSelectedOption() {
		final String[] selectedItems = optionList.getSelection();
		
		if( selectedItems.length > 0 )
			return selectedItems[0];
		else
			return null;
	}

	private boolean matchesFilter(String word, String filter) {
		try {
			return word.toLowerCase().matches(filter.toLowerCase());
		} catch (Throwable e) {
			// matches throws RuntimeExceptions...
			return false;
		}
	}
	
	private void applyFilter(String filter) {
		final String regexpr = ".*" + filter + ".*";
		
		optionList.removeAll();
		
		for(String opt : options) {
			if( matchesFilter(opt, regexpr) ) {
				optionList.add(opt);
			}
		}
		
		optionList.setSelection(0);
	}
	
	private void initialize() {
		GridData gridData1 = new org.eclipse.swt.layout.GridData();
		gridData1.horizontalAlignment = org.eclipse.swt.layout.GridData.FILL;
		gridData1.verticalAlignment = org.eclipse.swt.layout.GridData.CENTER;
		GridData gridData = new org.eclipse.swt.layout.GridData();
		gridData.horizontalAlignment = org.eclipse.swt.layout.GridData.FILL;
		gridData.grabExcessHorizontalSpace = true;
		gridData.grabExcessVerticalSpace = true;
		gridData.verticalAlignment = org.eclipse.swt.layout.GridData.FILL;
		GridLayout gridLayout = new GridLayout();
		gridLayout.makeColumnsEqualWidth = false;
		gridLayout.numColumns = 1;
		text = new Text(this, SWT.BORDER);
		text.setLayoutData(gridData1);
		text.addModifyListener(new org.eclipse.swt.events.ModifyListener() {
			public void modifyText(org.eclipse.swt.events.ModifyEvent e) {
				applyFilter(text.getText());
			}
		});
		optionList = new List(this, SWT.NONE);
		optionList.setLayoutData(gridData);
		this.setLayout(gridLayout);
		setSize(new org.eclipse.swt.graphics.Point(320,262));
	}
	
	/*
	public static void main(String[] args) {
		Display display = Display.getDefault();

		final Shell wnd = new Shell(display);
		wnd.setSize(400, 300);
		wnd.open();
		
		wnd.addMouseListener(new MouseListener() {
			public void mouseUp(MouseEvent e) {
				FilterDialog dlg = new FilterDialog(wnd);
				for(int i = 0; i < 10; ++i) {
					dlg.addOption("option        : " + i);
				}
				String result = dlg.open();
				System.out.println("Result is " + result);
			}
		
			public void mouseDown(MouseEvent e) {}
			public void mouseDoubleClick(MouseEvent e) {}
		});
		
		while (!wnd.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		
		display.dispose();
	}
	*/
}  //  @jve:decl-index=0:visual-constraint="10,10"
