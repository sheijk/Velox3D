/**
 * 
 */
package de.velox.editor;

import org.eclipse.jface.action.Action;

import de.velox.IVSynchronizedAction;
import de.velox.VView;

public abstract class SyncAction extends Action {
	public SyncAction() {
		super();
	}
	
	public SyncAction(String name) {
		setText(name);
	}
	
	@Override public final void run() {
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override public void Run() {
				try {
					exec();
				}
				catch(RuntimeException e) {
					System.err.println("Exception occured: " +
							e.getMessage());
				}
			}
		});
	}
	
	protected abstract void exec();
}