package de.velox.editor.scene;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.commands.IHandler;
import org.eclipse.core.commands.IHandlerListener;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.ui.IEditorActionDelegate;
import org.eclipse.ui.IEditorPart;

import de.velox.editors.SceneEditor;

/**
 * Handles the menu/toolbar command and the keyboard shortcut and notifies
 * the active SceneEditor of it
 * 
 * (pretty hacky, but works. let us know if you found a better way to do this) 
 * @author sheijk
 */
public class ActivateInputAction implements IEditorActionDelegate, IHandler {
	// static because there are two instances, one for the
	// IEditorActionDelegate of the org.eclipse.ui.editorAction
	// and one for the IHandler of the org.eclipse.ui.commands
	private static SceneEditor sceneEditor = null;
	
	/** Store the active editor if it is changed by the user */
	public void setActiveEditor(IAction action, IEditorPart targetEditor) {
		System.out.println("ActivateInputAction.setActiveEditor(" + targetEditor + ")");
		if( targetEditor instanceof SceneEditor ) {
			sceneEditor = (SceneEditor)targetEditor;
		}
		else {
			sceneEditor = null;
		}
	}
	
	private void exec() {
		if( sceneEditor != null ) {
			sceneEditor.enableInput();
		}
		else {
			System.err.println("ActivateInputAction.sceneEditor = null");
		}
	}

	public void run(IAction action) {
		exec();
	}

	public void selectionChanged(IAction action, ISelection selection) {}

	// IHandler methods
	public Object execute(ExecutionEvent event) throws ExecutionException {
		exec();
		return null;
	}
	public boolean isEnabled() { return true; }
	public boolean isHandled() { return true; }
	
	public void addHandlerListener(IHandlerListener handlerListener) {}
	public void dispose() {}
	public void removeHandlerListener(IHandlerListener handlerListener) {}
}
