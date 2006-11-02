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
 * Handles keys and menu/toolbar commands to restore the scene
 * 
 * @author sheijk
 * @see de.velox.editor.scene.ActivateInputAction
 */
public class RestoreSceneAction implements IHandler, IEditorActionDelegate {
	private static SceneEditor sceneEditor = null;

	public void setActiveEditor(IAction action, IEditorPart targetEditor) {
		if( targetEditor instanceof SceneEditor ) {
			sceneEditor = (SceneEditor)targetEditor;
		}
		else {
			sceneEditor = null;
		}
	}

	public void run(IAction action) {
		exec();
	}
	
	private void exec() {
		if( sceneEditor != null ) {
			sceneEditor.restoreScene();
		}
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
